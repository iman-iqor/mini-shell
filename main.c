#include "./includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_general	g_general;

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

	g_general.PATH = "PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin";
	g_general.PWD = "PWD=/home/imiqor/Desktop/minishell";
	(void)argc;
	(void)argv;
	ft_gc(0, 's');
	check_env(env, &my_env_list);
	signal(SIGINT, h);
	signal(SIGQUIT, SIG_IGN);
	env_list_to_array(my_env_list);
	while (1)
	{
		input = readline("minishell::::::");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		list = parse_cmd(input, my_env_list);
		ft_exec(list);
		printf("%d\n", g_general.exit_status);
		free(input);
	}
	graceful_exit();
	return (0);
}
