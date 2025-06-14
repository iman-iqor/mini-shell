#include "../../includes/minishell.h"

void	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg && msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}