/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:48 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/17 18:22:05 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_no_input(t_list *list)
{
	int		fd_out;
	t_file	*tmp;

	fd_out = -1;
	tmp = list->output_file;
	while (tmp)
	{
		if (fd_out != -1)
			close(fd_out);
		if (tmp->flag)
			fd_out = open(tmp->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			output_no_input_error(tmp, list);
			exit(1) ;
		}
		dup2(fd_out, STDOUT_FILENO);
		tmp = tmp->next;
	}
	close(fd_out);
}

void	input_output(t_list *list, t_env *env)
{
	input_no_output(list, env);
	if (!list->error_flag)
		output_no_input(list);
}

void	wait_and_update_status(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_general.exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_general.exit_status = 130;
			write(1, "\n", 1);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			g_general.exit_status = 131;
			write(2, "Quit (core dumped)\n", 20);
		}
	}
	signal(SIGINT, h);
}

void	exec_externals(t_list *list)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		g_general.exit_status = 1;
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if(!execute_command(list))
			ft_gc(0, 'f');
	}
	else
	{
		wait_and_update_status(pid);
	}
}

void	ft_redirect_and_execute(t_list *list, t_env *env)
{
	if (list->input_file && !list->output_file)
		input_no_output(list, env);
	else if (!list->input_file && list->output_file)
		output_no_input(list);
	else if (list->input_file && list->output_file)
		input_output(list, env);
	if (list->error_flag)
		return ; // Skip execution due to redirection error
	if (list->argument)
	{
		if (is_builtin(list->argument[0]))
			exec_builtin(list);
		else
			exec_externals(list);
	}
}
