/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:54:01 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 21:36:02 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			exit(1);
		}
		tmp = tmp->next;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	handle_child_process(t_list *list, t_exec_data *d)
{
	set_signals_child();
	if (list->input_file)
		input_no_output_of_pipe(list);
	else if (d->prev_fd != -1)
		dup2(d->prev_fd, 0);
	if (list->output_file)
		output_no_input_pipe(list);
	else if (list->next)
		dup2(d->pipe_fd[1], 1);
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
