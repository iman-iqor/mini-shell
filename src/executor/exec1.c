#include "../includes/minishell.h"
void	pwd(void);

void	exec_builtin(t_list *list)
{
	if (list && ft_strcmp("echo", list->argument[0]) == 0)
		echo(list->argument + 1);
	if (list && ft_strcmp("cd", list->argument[0]) == 0)
		cd(list->argument + 1);
	if (list && ft_strcmp("env", list->argument[0]) == 0)
		env();
	if (list && ft_strcmp("exit", list->argument[0]) == 0)
		ft_exit(list->argument + 1);
	if (list && ft_strcmp("export", list->argument[0]) == 0)
		export(list->argument + 1);
	if (list && ft_strcmp("pwd", list->argument[0]) == 0)
		pwd();
	if (list && ft_strcmp("unset", list->argument[0]) == 0)
		unset(list->argument + 1);
}


int	is_builtin(char *cmd)
{
	char const	*builtins[] = {"echo", "cd", "env", "exit", "export", "pwd",
		"unset", NULL};
	int			i;

	i = 0;
	while (cmd && builtins[i])
	{
		if (ft_strcmp(cmd, (char *)builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}


void execone(t_list *list)
{
	if(list->input_file && !list->heredoc)
	{
		//hna ghandir khdma dyal nakhod fd dyal dak l input file wnqra mnou
	}
	else if(list->input_file && list->heredoc)
	{
		//hna fin ghandir l heredoc wnqra mn tmp file 
		int fd_input_file;
		fd_input_file = heredoc(list);
		printf("%d\n",fd_input_file);


	}
	else if(!list->input_file && !list->heredoc)
	{
		//hna ghadi n executi 3adi
	}
}

int	ft_exec_single_command(t_list *list)
{
	
	if (list && !list->next)
	{
		if(is_builtin(list->argument[0]))
		{
			printf("enetered is_builtins w rah dakhl l exec builtin\n");
			exec_builtin(list);

		}
		else
		{
			printf("entered execone\n");
			execone(list);
		}
		return 1;
	}
	return (0);
}



void	ft_exec(t_list *list)
{
	printf("entered ft_exec at least!\n");
	if (ft_exec_single_command(list))
		return ;
	// if (ft_exec2(list))
	// 	return ;
	// ft_exec3(list);
	// while (wait(NULL) > 0)
	// 	;
}