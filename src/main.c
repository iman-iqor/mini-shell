/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:21:19 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/14 10:57:17 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int main()
{
    char    *input;
    char    **arguments;
    int     num_arg;
    while (1)
    {
        input = readline("minishell> ");
        if (input == NULL)
            break;
        if (*input)
            add_history(input);
        arguments = ft_split(input, ' ');
        num_arg = count_words(input, ' ');
        free(input);
    }
    return 0;
}