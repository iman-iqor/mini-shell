#include "../../includes/minishell.h"

void	exec_builtin(t_list *list)
{
	if (list && ft_strcmp("echo", list->argument[0]) == 0)
		echo(list->argument + 1);
	// if (list && ft_strcmp("cd", list->argument[0]) == 0)
	// 	cd(list->argument + 1);
	
}