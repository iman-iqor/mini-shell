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

void	execone(t_list *list)
{
	int	fd;

	if (list && list->input_file && !list->output_file)
	{
		if (list->input_file && !list->input_file->flag)
		{
			// here i ll need to open that file and get it fd to make my input for my command
			fd = open(list->input_file->file_name, O_RDONLY);
			if (fd == -1)
			{
				perror(list->input_file->file_name);
				return ;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (list->input_file && list->input_file->flag)
		{
			// here i know that i have a heredoc or multiple heredocs or i dont help
			if (heredoc(list) == -1)
			{
				perror("heredoc failed");
				return ;
			}
			if (list->fd != -1)
			{
				dup2(list->fd, STDIN_FILENO);
				close(list->fd);
			}
		}
	}
	else if(list && !list->input_file && list->output_file)
	{
		//case where i ll have just the output file
	}
	else if(list && list->input_file && list->output_file)
	{
		//case where i ll have the both input and output files
	}
	else if (list && !list->input_file && !list->output_file)
	{
		// here i dont have any input file i will execute normal
	}
	else if(!list)
	{
		//error because there is no list att all ,just for more protection
	}
}

int	ft_exec_single_command(t_list *list)
{
	if (list && list->next == NULL)
	{
		if (list->argument != NULL && is_builtin(list->argument[0]))
		{
			exec_builtin(list);
		}
		else
		{
			execone(list);
		}
		return (1);
	}
	return (0);
}

void	ft_exec(t_list *list)
{
	if (ft_exec_single_command(list))
		return ;
	// if (ft_exec2(list))
	// 	return ;
	// ft_exec3(list);
	// while (wait(NULL) > 0)
	// 	;
}