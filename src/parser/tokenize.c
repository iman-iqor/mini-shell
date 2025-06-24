/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:11:48 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/06/24 18:43:24 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_operator(char *input, int *i, t_quote_type *quote_type)
{
	char	*operator;

	if (!ft_strncmp(input + *i, ">>", 2) || !ft_strncmp(input + *i, "<<", 2))
	{
		operator= ft_substr(input, *i, 2);
		*i += 2;
		if (input[*i] == '>' || input[*i] == '<')
			return (NULL);
	}
	else
	{
		operator= ft_substr(input, *i, 1);
		*i += 1;
		if (input[*i] == '|' || input[0] == '|' || input[*i] == '>'
			|| input[*i] == '<')
			return (NULL);
	}
	if (input[*i] == '\'')
		*quote_type = SINGLE_QUOTE;
	else if (input[*i] == '"')
		*quote_type = DOUBLE_QUOTE;
	return (operator);
}

char	*get_word(char *input, int *i, t_quote_type *quote_type)
{
	int		start;
	char	quote;

	start = *i;
	while (input[*i] && (input[*i] != '|' && input[*i] != '>'
			&& input[*i] != '<') && input[*i] > 32)
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] != quote)
				return (NULL);
			if (quote == '\'')
				*quote_type = SINGLE_QUOTE;
			else if (quote == '"')
				*quote_type = DOUBLE_QUOTE;
		}
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

static t_token	*new_token(char *value, t_token_type type,
		t_quote_type quote_type)
{
	t_token	*new_token;

	new_token = ft_gc(sizeof(t_token), 'm');
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->quote_type = quote_type;
	new_token->next = NULL;
	return (new_token);
}

static void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

t_token	*tokenize_input(char *input)
{
	t_token			*tokens;
	int				i;
	char			*value;
	t_token_type	type;
	t_quote_type	quote_type;

	tokens = NULL;
	i = 0;
	quote_type = NONE;
	while (input[i])
	{
		while (input[i] && input[i] <= 32)
			i++;
		if (!input[i])
			break ;
		value = process_input(input, &i, &quote_type);
		if (!value)
			return (NULL);
		if (value && value[0] > 32 && ft_strlen(value) >= 1)
		{
			type = get_token_type(value);
			add_token(&tokens, new_token(value, type, quote_type));
		}
	}
	return (tokens);
}
