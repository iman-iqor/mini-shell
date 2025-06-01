
#include "../../includes/minishell.h"

void	graceful_exit(void)
{
	ft_gc(0, 'f');  
	ft_gc(0,'p'); 
	if (g_general.in > 2)
		close(g_general.in);
	if (g_general.out > 2)
		close(g_general.out);
}