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
	t_env	*env;

	(void)argc;
	(void)argv;
	list = NULL;
	env = init_env(env);  //check
	while (1)
	{
		input = readline("minishell$ ");
		if (ft_strlen(input) > 0)
			add_history(input);
		parse_cmd(input, env);
		free(input);
	}
	return (0);
}
