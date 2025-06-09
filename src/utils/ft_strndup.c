#include "../../includes/minishell.h"
char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_gc(n + 1, 'm');
	while (n > i)
	{
		s[i] = str[i];
		i++;
	}
	s[n] = 0;
	return (s);
}
