/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 10:43:25 by mbenjbar          #+#    #+#             */
/*   Updated: 2025-04-21 10:43:25 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    parse_cmd(char *input, t_env *env)
{
    t_token *tokens;
    char    *value_env;
    if ((input == NULL || !ft_strncmp(input, "exit", 4))
	&& (ft_strlen(input) == 4))
    {
	    printf("exit\n");
	    free(input);
	    exit(0);
    }
    // split the cmd to tokens
    tokens = tokenize_input(input);
    // command that looks for the value of the key of the env you give it
    value_env = get_env_value(env, "USER");
	if (value_env)
		printf("The value is: %s\n", value_env);
	else
		printf("we couldn't find the value of this key\n");
    // expand the env variables
	expand_variables(tokens, env);
}
