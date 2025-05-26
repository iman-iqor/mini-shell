#include "./includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_general	g_general;

void	h(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	//srl_replace_line("", 0);
	rl_redisplay();
}


int	main(int argc, char **argv, char **env)
{
	t_list	*list;
	t_env	*my_env_list;
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	my_env_list = init_env_list(env);
	signal(SIGINT, h);
	signal(SIGQUIT, SIG_IGN);
	env_list_to_array(my_env_list);
	while (1)
	{
		input = readline("\033[1;92m➜  \033[1;36mminishell\033[0m ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		list = parse_cmd(input, my_env_list);
		ft_exec(list);
		free(input);
	}
	void graceful_exit(void);
	return (0);
}
