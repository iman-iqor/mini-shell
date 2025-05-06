/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:31:40 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/05 22:52:04 by mbenjbar         ###   ########.fr       */
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

	(void)argv;
	if (argc != 1)
		printf("Error: try only 1 argument");
	env = init_env(envp);
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
			continue;
		}
		parse_cmd(input, env);
		free(input);
	}
	clear_history();
	return (0);
}
