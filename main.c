#include "./includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_general	g_general;

static int	is_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 32)
			return (1);
		i++;
	}
	return (0);
}

void	h(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_list	*list;
	t_env	*my_env_list;
	char	*input;

	if (argc != 1)
		exit(printf("Error: try only 1 argument"));
	g_general.PATH = "PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin";
	g_general.PWD = "PWD=/home/imiqor/Desktop/minishell";
	(void)argc;
	(void)argv;
	ft_gc(0, 's');
	check_env(env, &my_env_list);
	signal(SIGINT, h);
	signal(SIGQUIT, SIG_IGN);
	g_general.env_array = env_list_to_array(my_env_list);
	while (1)
	{
		input = readline("\033[1;92m➜  \033[1;36mminishell\033[0m ");
		if (input == NULL)
		{
			printf("exit\n");
			// free everything here
			break ;
		}
			if (ft_strlen(input) > 0)
			add_history(input);
		if (is_only_spaces(input) == 0)
		{
			free(input);
			continue ;
		}
		list = parse_cmd(input, my_env_list);
		if (list != NULL)
			ft_exec(list);
		// printf("%d\n", g_general.exit_status);
		free(input);
	}
	clear_history();
	graceful_exit();
	return (0);
}
