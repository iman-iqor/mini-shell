#include "../../includes/minishell.h"

void	ft_putstr(char *text)
{
	int	i;

	i = 0;
	while (text && text[i])
		write(1, text + i++, 1);
}