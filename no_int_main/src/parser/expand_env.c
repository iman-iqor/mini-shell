/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:18:27 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/06 18:46:38 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

static char	*expand_value(char *word, t_env *env)
{
	int		i;
	int		start;
	char	*result;
	char	*var_value;
	char	*tmp;
	char	*key;

	i = 0;
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] && (ft_isalpha(word[i + 1]) || word[i
				+ 1] == '_'))
		{
			i++;
			start = i;
			while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
				i++;
			key = ft_substr(word, start, i - start);
			var_value = get_env_value(env, key);
			if (!var_value)
				var_value = ft_strdup("");
			tmp = ft_strjoin(result, var_value);
			free(result);
			free(var_value);
			result = tmp;
			free(key);
		}
		else
		{
			result = ft_strjoin_char(result, word[i]);
			i++;
		}
	}
	return (result);
}

void expand_variables(t_token *tokens, t_env *env)
{
	char *expanded_value;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && ft_strchr(tokens->value, '$'))
		{
			if (tokens->quote_type != SINGLE_QUOTE)
			{
				expanded_value = expand_value(tokens->value, env);
				if (tokens->value)
					free(tokens->value);
				tokens->value = expanded_value;
			}
		}
		tokens = tokens->next;
	}
}
