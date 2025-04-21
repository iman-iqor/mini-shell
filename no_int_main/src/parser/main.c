/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 10:31:40 by mbenjbar          #+#    #+#             */
/*   Updated: 2025-04-21 10:31:40 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*list;

	(void)argc;
	(void)argv;
	list = NULL;
	init_env(env);  //check
	while (1)
	{
		input = readline("minishell$ ");
		if ((input == NULL || !ft_strncmp(input, "exit", 4))
		&& (ft_strlen(input) == 4))
	    {
		    printf("exit\n");
		    free(input);
		    exit(0);
	    }
		if (ft_strlen(input) > 0)
			add_history(input);
		parse_cmd(input);
		free(input);
	}
	return (0);
}
