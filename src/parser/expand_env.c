/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:18:27 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/06/24 21:21:59 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_of_expanding(char *word, int *i, char *result, t_env *env, int flag)
{
	if (word[*i] == '\'')
		result = case_of_squote(word, i, result);
	else if (word[*i] == '$' && word[*i + 1] && (ft_isalpha(word[*i + 1])
			|| word[*i + 1] == '_') && flag == 0)
		result = case_of_normal_var(word, i, result, env);
	else if (word[*i] == '"')
		result = case_of_dquote(word, i, result, env, flag);
	else if (word[*i + 1] && word[*i] == '$' && word[*i + 1] == '\'')
		result = case_of_var_with_next_char_squote(word, i, result);
	else if (word[*i + 1] && word[*i] == '$' && word[*i + 1] == '\"')
		result = case_of_var_with_next_char_dquote(word, i, result);
	else if (word[*i] == '$' && word[*i + 1] && ft_isdigit(word[*i + 1]) && flag == 0)
		result = case_of_var_with_next_char_digit(word, i, result);
	else if (word[*i] == '$' && word[*i + 1] && word[*i + 1] == '?' && flag == 0)
		result = case_of_var_with_exit_status(i, result);
	else
		result = case_of_word(word, i, result);
	return (result);
}

static char	*expand_variable_value(char *word, t_env *env, int flag)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (word[i])
		result = process_of_expanding(word, &i, result, env, flag);
	return (result);
}

void	expand_variables(t_token *tokens, t_env *env)
{
	char	*expanded_value;
	int		flag;

	flag = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (tokens->prev && tokens->prev->type == TOKEN_HEREDOC)
				flag = 1;
			expanded_value = expand_variable_value(tokens->value, env, flag);
			tokens->value = expanded_value;
		}
		tokens = tokens->next;
	}
}
