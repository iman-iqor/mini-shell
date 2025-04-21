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

void    parse_cmd(char *input)
{
    t_token *tokens;
    if ((input == NULL || !ft_strncmp(input, "exit", 4))
	&& (ft_strlen(input) == 4))
    {
	    printf("exit\n");
	    free(input);
	    exit(0);
    }
    // split the cmd to tokens
    tokens = tokenize_input(input);
}
