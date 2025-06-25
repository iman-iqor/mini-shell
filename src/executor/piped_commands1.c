/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:54:01 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 21:36:19 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
		g_general.exit_status = 1;
		return ;
	}
	if (heredoc_error_found(list))
	{
		g_general.exit_status = 1;
		return ;
	}
	execute_piped_loop(list, &d);
	wait_for_all(d.pid, d.n_cmd);
}
