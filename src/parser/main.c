/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:31:40 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/17 20:29:50 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_general	g_general;

static int	check_spaces(char *input)
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;
	t_list *cmds;

	(void)argv;
	if (argc != 1)
		printf("Error: try only 1 argument");
	env = init_env(envp); // it is working properly
	// while (env != NULL)
	// {
	// 	printf("%s=%s\n", env->key, env->value);
	// 	env = env->next;
	// }
	while (1)
	{
		input = readline("\033[1;92m➜  \033[1;36mminishell\033[0m ");
		if (!input)
			break ;
		if (ft_strlen(input) > 0)
			add_history(input);
		if (check_spaces(input) == 0)
		{
			free(input);
			break ;
		}
		cmds = parse_cmd(input, env);
		// while (cmds)
		// {
		// 	char **args = cmds->argument;
		// 	if (args && *args)
		// 		printf("this is the command and argumets: ");
		// 	while (args && *args)
		// 	{
		// 		printf("%s ", *args);
		// 		args++;
		// 	}
		// 	printf("\n");
		// 	t_file *in = cmds->input_file;
		// 	while (in)
		// 	{
		// 		printf("input file name is: %s and its flag is: %d\n", in->file_name, in->flag);
		// 		in = in->next;
		// 	}
		// 	t_file *out = cmds->output_file;
		// 	while (out)
        // 	{
		// 	    printf("output file name is: %s and its flag is: %d\n", out->file_name, out->flag);
		// 	    out = out->next;
	    // 	}
		// 		cmds = cmds->next;
		// }
		free(cmds);
		free(input);
	}
	clear_history();
	return (0);
}
