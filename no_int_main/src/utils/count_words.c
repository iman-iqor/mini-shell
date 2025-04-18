#include "../../includes/minishell.h"

int	ft_countword(const char *str, char c)
{
	int	countword;
	int	isinword;

	countword = 0;
	isinword = 0;
	while (*str)
	{
		isinword = 0;
		while (*str && *str == c)
		{
			str++;
		}
		while (*str && *str != c)
		{
			if (!isinword)
			{
				isinword = 1;
				countword += 1;
			}
			str++;
		}
	}
	return (countword);
}
