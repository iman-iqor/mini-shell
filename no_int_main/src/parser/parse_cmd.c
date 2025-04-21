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

t_token *tokenize_input(char *input)
{
    t_token *tokens = NULL;
    int i = 0;
    while (input[i] != '\0')
    {
        while (input[i] <= 32)
            i++;
        if (input[i] == '\0')
	    		break ;
    }
    return(tokens);
}

void    parse_cmd(char *input)
{
    t_token *tokens;
    tokens = tokenize_input(input);
}
