/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:58:06 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/06/24 18:42:21 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*init_cmd(t_list **cmd_list)
{
	t_list	*new_cmd;
	t_list	*tmp;

	new_cmd = ft_gc(sizeof(t_list), 'm');
	if (new_cmd == NULL)
		return (NULL);
	ft_bzero(new_cmd, sizeof(t_list));
	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->next = NULL;
	}
	return (new_cmd);
}

static int	redirections(t_list *current_cmd, t_token **tokens)
{
	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		return (0);
	if ((*tokens)->type == TOKEN_REDIRECT_IN)
		current_cmd = ft_add_file(current_cmd, (*tokens)->next->value, 0, 'i');
	if ((*tokens)->type == TOKEN_REDIRECT_OUT)
		current_cmd = ft_add_file(current_cmd, (*tokens)->next->value, 0, 'o');
	if ((*tokens)->type == TOKEN_APPEND)
		current_cmd = ft_add_file(current_cmd, (*tokens)->next->value, 1, 'o');
	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		current_cmd = ft_add_file(current_cmd, (*tokens)->next->value, 1, 'i');
		current_cmd->quote_type = (*tokens)->next->quote_type;
	}
	(*tokens) = (*tokens)->next;
	return (1);
}

static char	**ft_handle_word(t_list *current_cmd, t_token *tokens)
{
	char	**args;
	int		i;

	if (tokens->quote_type == NONE)
	{
		args = ft_split(tokens->value, ' ');
		i = 0;
		while (args[i])
		{
			current_cmd->argument = ft_realloc_array(current_cmd->argument,
					args[i]);
			i++;
		}
	}
	else
		current_cmd->argument = ft_realloc_array(current_cmd->argument,
				tokens->value);
	return (current_cmd->argument);
}

t_list	*parse_tokens(t_token *tokens)
{
	t_list	*cmd_list;
	t_list	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (current_cmd == NULL || tokens->type == TOKEN_PIPE)
		{
			current_cmd = init_cmd(&cmd_list);
			if (!current_cmd)
				return (NULL);
		}
		if (tokens->type == TOKEN_WORD)
			current_cmd->argument = ft_handle_word(current_cmd, tokens);
		else if (tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_APPEND || tokens->type == TOKEN_HEREDOC)
			if (!redirections(current_cmd, &tokens))
				return (NULL);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmd_list);
}
