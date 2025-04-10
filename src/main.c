/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:21:19 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/10 17:38:34 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int main()
{
      char *input;
    while (1)
    {
        input = readline("minishell> ");
        if (input == NULL)
            break;
        if (*input)
            add_history(input);
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}