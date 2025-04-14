/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:21:19 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/14 16:00:40 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_list list;
	// t_var var;
	char *input;
	// int num_arg;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		list.argument = ft_split(input, ' ');
		// num_arg = ft_countword(input, ' ');
		// var.i = 0;
		// while (var.i < num_arg)
		// {
		// 	printf("%s\n", list.argument[var.i]);
		// 	var.i++;
		// }
        exec_builtin(&list);

		free(input);
	}
	return (0);
}


