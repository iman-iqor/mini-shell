#include "../../includes/minishell.h"

char	*process_input(char *input, int *i, t_quote_type *quote_type)
{
	char	*value;

	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		value = get_operator(input, i, quote_type);
	else
		value = get_word(input, i, quote_type);
	if (!value)
		return (NULL);
	return (value);
}

t_token_type	get_token_type(char *value)
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

