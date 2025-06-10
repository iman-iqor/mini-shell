/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:54:01 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/10 21:54:02 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signals_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	wait_for_all(pid_t *pid, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			g_general.exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	handle_parent_process(t_exec_data *d, t_list *list)
{
	if (d->prev_fd != -1)
		close(d->prev_fd);
	if (list->next)
	{
		close(d->pipe_fd[1]);
		d->prev_fd = d->pipe_fd[0];
	}
	else
	{
		// Last command - close both ends
		close(d->pipe_fd[0]);
		close(d->pipe_fd[1]);
		d->prev_fd = -1;
	};
}

void	close_unused_fds(t_exec_data *d)
{
	if (d->prev_fd != -1)
		close(d->prev_fd);
	if (d->pipe_fd[0] != -1)
		close(d->pipe_fd[0]);
	if (d->pipe_fd[1] != -1)
		close(d->pipe_fd[1]);
}

void	input_no_output_of_pipe(t_list *list)
{
	int		fd_in;
	t_file	*tmp;

	tmp = list->input_file;
	fd_in = -1;
	while (tmp)
	{
		if (fd_in != -1)
			close(fd_in);
		fd_in = open(tmp->file_name, O_RDONLY);
		if (fd_in == -1)
		{
			perror(tmp->file_name);
			list->error_flag = 1;
			return ;
		}
		tmp = tmp->next;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	handle_child_process(t_list *list, t_exec_data *d)
{
	set_signals_child();
	if (d->prev_fd != -1)
		dup2(d->prev_fd, 0);
	else if (list->input_file)
		input_no_output_of_pipe(list);
	if (list->next)
		dup2(d->pipe_fd[1], 1);
	else if (list->output_file)
		output_no_input(list);
	close_unused_fds(d);
	execute_command(list);
}

void	init_exec_data(t_exec_data *d, t_list *list)
{
	d->i = 0;
	d->n_cmd = list_len(list);
	d->prev_fd = -1;
	d->pid = ft_gc(d->n_cmd * sizeof(pid_t), 'm');
}

int	handle_all_heredocs(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->input_file && tmp->input_file->flag)
		{
			if (heredoc(tmp, tmp->input_file) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc_error_found(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->error_flag)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_pipe_error(t_exec_data *d)
{
	if (pipe(d->pipe_fd) == -1)
	{
		perror("pipe");
		g_general.exit_status = 1;
		return (-1);
	}
	return (0);
}

int	handle_fork_and_process(t_list *list, t_exec_data *d)
{
	d->pid[d->i] = fork();
	if (d->pid[d->i] == -1)
	{
		perror("fork");
		g_general.exit_status = 1;
		return (-1);
	}
	if (d->pid[d->i] == 0)
	{
		handle_child_process(list, d);
		ft_gc(0, 'f');
	}
	else
	{
		set_signals_parent();
		handle_parent_process(d, list);
	}
	return (0);
}

void	execute_piped_loop(t_list *list, t_exec_data *d)
{
	while (list)
	{
		if (list->next)
		{
			if (handle_pipe_error(d) == -1)
				return ;
		}
		if (handle_fork_and_process(list, d) == -1)
			return ;
		list = list->next;
		d->i++;
	}
}

void	ft_exec_piped_commands(t_list *list)
{
	t_exec_data	d;

	set_signals_parent();
	init_exec_data(&d, list);
	if (handle_all_heredocs(list) == -1)
		return ;
	if (heredoc_error_found(list))
	{
		g_general.exit_status = 1;
		return ;
	}
	execute_piped_loop(list, &d);
	wait_for_all(d.pid, d.n_cmd);
}
