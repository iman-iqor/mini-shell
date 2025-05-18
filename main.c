#include "./includes/minishell.h"

t_general	g_general;

void h(int sig)
{
	(void)sig;
	// printf("AWDN");
	// printf("\n");
	ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_list	*list;
	t_env	*my_env_list;
	char	*input;

	;
	(void)argc;
	(void)argv;
	(void)env;
	my_env_list = init_env_list(env);
	// signal(SIGINT, h);
    signal(SIGINT, h); 
	signal(SIGQUIT, SIG_IGN);
	env_list_to_array(my_env_list);
	while (1)
	{
		printf("main\n");

		input = readline("mminishell  ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		printf("parse\n");
		list = parse_cmd(input, my_env_list);
        printf("hello\n");
        ft_exec(list);
        // printf("%s \n",list->argument[0]);
		// printf("%c %d\n",list->input_file->file_name[0],list->input_file->flag);
		// printf("%c\n",list->input_file->next->file_name[0]);
		// printf("%c\n",list->input_file->next->next->file_name[0]);

		free(input);
	}
	void graceful_exit(void);
	return (0);
}
