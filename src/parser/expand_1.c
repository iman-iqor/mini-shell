#include "../../includes/minishell.h"

char	*case_of_squote(char *word, int *i, char *result)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
	{
		result = ft_strjoin_char(result, word[*i]);
		(*i)++;
	}
	if (word[*i])
		(*i)++;
	return (result);
}

char	*case_of_dquote(char *word, int *i, char *result, t_env *env)
{
	(*i)++;
	while (word[*i] && word[*i] != '"')
	{
		if (word[*i] == '$' && word[*i + 1] && (ft_isalnum(word[*i + 1])
				|| word[*i + 1] == '_'))
			result = case_of_normal_var(word, i, result, env);
		else if (word[*i] == '$' && word[*i + 1] && word[*i + 1] == '?')
		{
			(*i) += 2;
			// result = ft_strjoin(result, ft_itoa(g_exit_status));
		}
		else
		{
			result = ft_strjoin_char(result, word[*i]);
			(*i)++;
		}
	}
	if (word[*i])
		(*i)++;
	return (result);
}

char	*case_of_normal_var(char *word, int *i, char *result, t_env *env)
{
	int (start), (j);
	char *(key), *(value);
	(*i)++;
	start = (*i);
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		(*i)++;
	key = ft_substr(word, start, (*i) - start);
	value = get_env_value(env, key);
	if (!value)
		value = ft_strdup("");
	j = 0;
	while (value[j])
	{
		while (value[j] && value[j] <= 32 && value[j + 1] <= 32)
			j++;
		if (value[j])
		{
			result = ft_strjoin_char(result, value[j]);
			j++;
		}
	}
	return (result);
}

char	*case_of_var_with_next_char_squote(char *word, int *i, char *result)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
	{
		result = ft_strjoin_char(result, word[*i]);
		(*i)++;
	}
	if (word[*i])
		(*i)++;
	return (result);
}

char	*case_of_var_with_next_char_dquote(char *word, int *i, char *result)
{
	(*i)++;
	while (word[*i] && word[*i] != '\"')
	{
		result = ft_strjoin_char(result, word[*i]);
		(*i)++;
	}
	if (word[*i])
		(*i)++;
	return (result);
}
