#include "./includes/minishell.h"

t_general	g_general;

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
	env_list_to_array(my_env_list);
	while (1)
	{
		input = readline("\033[1;32mminishell>\033[0m ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
        printf("a\n");
		list = parse_cmd(input, my_env_list);
        // printf("%s\n",list->input_file[0]);
        // printf("%d\n",list->heredoc);
        ft_exec(list);
        
		free(input);
	}
	void graceful_exit(void);
	return (0);
}
