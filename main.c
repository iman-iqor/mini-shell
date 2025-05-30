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

// void	graceful_exit(void)
// {
// 	ft_gc(0, 'f');  
// 	ft_gc(0,'p');            // Free all allocated memory
// 	if (g_general.in > 2)
// 		close(g_general.in);
// 	if (g_general.out > 2)
// 		close(g_general.out);
// }
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
		input = readline("minishell::::::");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		list = parse_cmd(input, my_env_list);
		ft_exec(list);
		printf("%d\n",g_general.exit_status);
		free(input);
	}
	graceful_exit();
	return (0);
}
