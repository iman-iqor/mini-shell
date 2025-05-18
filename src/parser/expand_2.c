#include "../../includes/minishell.h"

char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		i;

	new_str = ft_gc(sizeof(char) * (ft_strlen(str) + 2), 'm');
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
	return (new_str);
}

char	*case_of_var_with_next_char_digit(char *word, int *i, char *result)
{
	(*i) += 2;
	while (word[*i])
	{
		result = ft_strjoin_char(result, word[*i]);
		(*i)++;
	}
	if (word[*i])
		(*i)++;
	return (result);
}

char	*case_of_var_with_exit_status(int *i, char *result)
{
	(*i) += 2;
	// result = ft_strjoin(result, ft_itoa(g_exit_status));
	return (result);
}

char	*case_of_word(char *word, int *i, char *result)
{
	result = ft_strjoin_char(result, word[*i]);
	(*i)++;
	return (result);
}
