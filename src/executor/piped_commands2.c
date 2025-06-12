/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:54:01 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/12 22:34:49 by imiqor           ###   ########.fr       */
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
