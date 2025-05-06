// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   generate_cmds.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/05 21:58:06 by mbenjbar          #+#    #+#             */
// /*   Updated: 2025/05/05 22:00:54 by mbenjbar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// t_list	*parse_tokens(t_token *tokens)
// {
// 	t_list		*cmd_list;
// 	t_list		*current_cmd;
// 	t_quote_type	quote_type;
// 	t_list		*tmp;

// 	cmd_list = NULL;
// 	current_cmd = NULL;
// 	quote_type = NONE;
// 	while (tokens)
// 	{
// 		// if we found a new command or | pipe
// 		if (!current_cmd || tokens->type == TOKEN_PIPE)
// 		{
// 			current_cmd = malloc(sizeof(t_list));
// 			if (!current_cmd)
// 				return (NULL);
// 			ft_bzero(current_cmd, sizeof(t_list));
// 			// add the new element to list
// 			if (!cmd_list)
// 				cmd_list = current_cmd;
// 			else
// 			{
// 				tmp = cmd_list;
// 				while (tmp->next)
// 					tmp = tmp->next;
// 				tmp->next = current_cmd;
// 			}
// 		}
// 		// add token to arguments (struct commands)
// 		if (tokens->type == TOKEN_WORD)
// 			current_cmd->arguments = ft_realloc_array(current_cmd->arguments,
// 					tokens->value);
// 		else if (tokens->type == TOKEN_REDIRECT_IN)
// 		{
// 			// move to the next token
// 			tokens = tokens->next;
// 			if (tokens)
// 				current_cmd->input_file = ft_realloc_array(current_cmd->input_file,
// 						tokens->value);
// 		}
// 		else if (tokens->type == TOKEN_REDIRECT_OUT)
// 		{
// 			tokens = tokens->next;
// 			if (tokens)
// 				current_cmd->output_file = ft_realloc_array(current_cmd->output_file,
// 						tokens->value);
// 			// apped = 0 because when we use redirect out (>) we using over write
// 			current_cmd->append = 0;
// 		}
// 		else if (tokens->type == TOKEN_APPEND)
// 		{
// 			tokens = tokens->next;
// 			if (tokens)
// 				current_cmd->output_file = ft_realloc_array(current_cmd->output_file,
// 						tokens->value);
// 			// apped = 1 because when we use append (>>) we using append
// 			current_cmd->append = 1;
// 		}
// 		// condition of heredoc
// 		else if (tokens->type == TOKEN_HEREDOC)
// 		{
// 			tokens = tokens->next;
// 			if (tokens)
// 			{
// 				current_cmd->input_file = ft_realloc_array(current_cmd->input_file,
// 						tokens->value);
// 				current_cmd->quote_type = tokens->quote_type;
// 			}
// 			// heredoc = 1 because when we use heredoc (<<) we using heredoc
// 			current_cmd->heredoc = 1;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (cmd_list);
// }
