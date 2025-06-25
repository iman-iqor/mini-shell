/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:43:25 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/06/25 16:54:54 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_cmds(t_token *tokens)
{
	t_token	*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens)
	{
		if (tmp_tokens->type == TOKEN_PIPE && tmp_tokens->next == NULL)
			return (0);
		if (tmp_tokens->type == TOKEN_PIPE)
		{
			tmp_tokens = tmp_tokens->next;
			if (tmp_tokens->type == TOKEN_PIPE)
				return (0);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (1);
}

t_list	*parse_cmd(char *input)
{
	t_token	*tokens;
	t_list	*cmds;

	tokens = tokenize_input(input);
	if (!tokens)
	{
		g_general.exit_status = 2;
		print_error("minishell: syntax error\n");
		return (NULL);
	}
	expand_variables(tokens);
	cmds = parse_tokens(tokens);
	if (!cmds || !check_cmds(tokens))
	{
		g_general.exit_status = 2;
		print_error("minishell: syntax error\n");
		return (NULL);
	}
	return (cmds);
}
