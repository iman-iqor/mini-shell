
#include "../../includes/minishell.h"
void rl_clear_history();
void	graceful_exit(void)
{
	ft_gc(0, 'f');              // Free all allocated memory
	if (g_general.in > 2)
		close(g_general.in);
	if (g_general.out > 2)
		close(g_general.out);
}