/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:43:25 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/16 14:04:10 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list*    parse_cmd(char *input, t_env *env)
{
    t_token *tokens;
    t_list *cmds;
    if ((input == NULL || !ft_strncmp(input, "exit", 4))
	&& (ft_strlen(input) == 4))
    {
	    printf("exit\n");
	    free(input);
	    exit(0);
    }
    // split the cmd to tokens
    tokens = tokenize_input(input);
    // t_token *tmp = tokens;
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
    //this one will be used for the execution part 
    cmds = parse_tokens(tokens);
    free_tokens(tokens);
    (void)cmds;
    // t_list *tmp1 = cmds;
    // while (tmp1)
    // {   
    //     char **args = tmp1->argument;
    //     printf("arguments: ");
    //     while (args && *args)
    //     {
    //         printf("%s", *args);
    //         args++;
    //     }
    //     printf("\n");
    //     char **output = tmp1->output_file;
    //     while (output && *output)
    //     {
    //         printf("wa hada l output file:%s", *output);
    //         output++;
    //     }
    //     printf("\n");
    //     char **input = tmp1->input_file;
    //     while (input && *input)
    //     {
    //         printf("input files:%s", *input);
    //         input++;
    //     }
    //     printf("\n");
    //     tmp1 = tmp1->next;
    // }
    return cmds;
}
