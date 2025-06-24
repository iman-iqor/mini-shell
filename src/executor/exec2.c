/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:48 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 20:35:36 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_list *list)
{
	if (!list || !list->argument || !list->argument[0])
		return ;
	if (ft_strcmp("echo", list->argument[0]) == 0)
		echo(list->argument + 1);
	else if (ft_strcmp("cd", list->argument[0]) == 0)
		cd(list->argument + 1);
	else if (ft_strcmp("env", list->argument[0]) == 0)
	{
		if (list->argument[1])
		{
			write(2, "Minishell:options are not supported\n", 37);
			g_general.exit_status = 127;
			return ;
		}
		env();
	}
	else if (ft_strcmp("exit", list->argument[0]) == 0)
		ft_exit(list->argument + 1);
	else if (ft_strcmp("export", list->argument[0]) == 0)
		export(list->argument + 1);
	else if (ft_strcmp("pwd", list->argument[0]) == 0)
		pwd();
	else if (ft_strcmp("unset", list->argument[0]) == 0)
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

void	input_no_output_error(t_file *tmp, t_list *list)
{
	perror(tmp->file_name);
	g_general.exit_status = 1;
	list->error_flag = 1;
}

void	input_no_output(t_list *list, t_env *env)
{
	int		fd_in;
	t_file	*tmp;

	tmp = list->input_file;
	fd_in = -1;
	while (tmp)
	{
		if (fd_in != -1)
			close(fd_in);
		if (tmp->flag)
		{
			if (heredoc(list, tmp, env) == -1)
				return ;
		}
		fd_in = open(tmp->file_name, O_RDONLY);
		if (fd_in == -1)
		{
			input_no_output_error(tmp, list);
			list->error_flag = 1;
			return ;
		}
		tmp = tmp->next;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	output_no_input_error(t_file *tmp, t_list *list)
{
	perror(tmp->file_name);
	g_general.exit_status = 126;
	list->error_flag = 1;
}
