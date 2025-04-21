/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 17:11:48 by mbenjbar          #+#    #+#             */
/*   Updated: 2025-04-21 17:11:48 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_quote_value(char *input, int *i, t_quote_type *quote_type)
{
	char	quote;
	int		start;
	char	*value;

	quote = input[*i];
	(*i)++;
	start = (*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	value = ft_substr(input, start, *i - start);
	if (input[*i] == quote)
		(*i)++;
	if (quote == '\'')
	    *quote_type = SINGLE_QUOTE;
	else
		*quote_type = DOUBLE_QUOTE;
	return (value);
}

static char	*get_operator(char *input, int *i)
{
	char	*operator;

	if (!ft_strncmp(input + *i, ">>", 2) || !ft_strncmp(input + *i, "<<", 2))
	{
		operator= ft_substr(input, *i, 2);
		*i = (*i) + 2;
	}
	else
	{
		operator= ft_substr(input, *i, 1);
		*i = (*i) + 2;
	}
	return (operator);
}

static char	*get_word(char *input, int *i)
{
	int     start;
    char    *value;

	start = *i;
	while (input[*i] && (input[*i] != '|' && input[*i] != '>'
			&& input[*i] != '<') && input[*i] > 32)
		(*i)++;
    value = ft_substr(input, start, *i - start);
	return (value);
}

static t_token_type	get_token_type(char *value)
{
	if (!ft_strncmp(value, ">>", 2))
		return (TOKEN_APPEND);
	else if (!ft_strncmp(value, "<<", 2))
		return (TOKEN_HEREDOC);
	else if (!ft_strncmp(value, "|", 1))
		return (TOKEN_PIPE);
	else if (!ft_strncmp(value, ">", 1))
		return (TOKEN_REDIRECT_OUT);
	else if (!ft_strncmp(value, "<", 1))
		return (TOKEN_REDIRECT_IN);
	return (TOKEN_WORD);
}

static t_token	*new_token(char *value, t_token_type type, t_quote_type quote_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
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

	if (*head == NULL)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

t_token *tokenize_input(char *input)
{
    t_token         *tokens = NULL;
    t_token_type	type;
    t_quote_type	quote_type;
    char            *value;
    int             i = 0;

    while (input[i] != '\0')
    {
        while (input[i] <= 32)
            i++;
        if (input[i] == '\0')
	    		break ;
       quote_type = NONE;
       // handle the single and double quote and get the what between the quotes
		if (input[i] == '\'' || input[i] == '"')
			value = get_quote_value(input, &i, &quote_type);
        // get the opearator | , > , < , << , or >>
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			value = get_operator(input, &i);
        // get the word if there is no quotes and no pipes etc...
		else
			value = get_word(input, &i);
        // add a type of token (PIPE, WORD, ...)
		type = get_token_type(value);
        // add the new token to the list of tokens
		add_token(&tokens, new_token(value, type, quote_type));
    }
    return(tokens);
}
