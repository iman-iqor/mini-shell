#include "../../includes/minishell.h"

void	exec_builtin(t_list *list)
{
	if (list && ft_strcmp("echo", list->argument[0]) == 0)
		echo(list->argument + 1);
	if (list && ft_strcmp("cd", list->argument[0]) == 0)
		cd(list->argument + 1);
	// if (list && ft_strcmp("env", list->argument[0]) == 0)
	// 	env();
	// if (list && ft_strcmp("exit", list->argument[0]) == 0)
	// 	ft_exit(list->argument + 1);
	// if (list && ft_strcmp("export", list->argument[0]) == 0)
	// 	export(list->argument + 1);
	// if (list && ft_strcmp("pwd", list->argument[0]) == 0)
	// 	pwd();
	// if (list && ft_strcmp("unset", list->argument[0]) == 0)
	// 	unset(list->argument + 1);
}