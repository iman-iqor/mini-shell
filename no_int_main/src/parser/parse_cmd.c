/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:43:25 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/06 19:20:06 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    parse_cmd(char *input, t_env *env)
{
    t_token *tokens;
    t_list *cmds;
    // t_token *tmp;
    if ((input == NULL || !ft_strncmp(input, "exit", 4))
	&& (ft_strlen(input) == 4))
    {
	    printf("exit\n");
	    free(input);
	    exit(0);
    }
    // split the cmd to tokens
    tokens = tokenize_input(input);
    // tmp = tokens;
    // while (tmp)
	// {
	// 	printf("TOKEN: [%s] Type: %d Quote: %d\n", tmp->value, tmp->type, tmp->quote_type);
	// 	tmp = tmp->next;
	// }
    // expand the env variables //it is working properly
	expand_variables(tokens, env);
    // tmp = tokens;
    // while (tmp)
	// {
	// 	printf("TOKEN: [%s] Type: %d Quote: %d\n", tmp->value, tmp->type, tmp->quote_type);
	// 	tmp = tmp->next;
	// }
    cmds = parse_tokens(tokens);
}
