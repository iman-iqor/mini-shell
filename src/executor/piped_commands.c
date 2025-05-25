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
		d->prev_fd = -1;
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
void	handle_child_process(t_list *list, t_exec_data *d)
{
	set_signals_child();

	if (list->input_file)
		input_no_output(list);  
	else if (d->prev_fd != -1)
		dup2(d->prev_fd, 0); 

	if (list->output_file)
		output_no_input(list);
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

void	ft_exec_piped_commands(t_list *list)
{
	t_exec_data	d;

	set_signals_parent();
	init_exec_data(&d, list);
	while (list)
	{
		if (list->next)
		{
			if (pipe(d.pipe_fd) == -1)
			{
				perror("pipe");
				g_general.exit_status = 1;
				return ;
			}
		}
		d.pid[d.i] = fork();
		if (d.pid[d.i] == -1)
		{
			perror("fork");
			g_general.exit_status = 1;
			return ;
		}
		if (d.pid[d.i] == 0)
			handle_child_process(list, &d);
		else
			handle_parent_process(&d, list);
		list = list->next;
		d.i++;
	}
	wait_for_all(d.pid, d.n_cmd);
}
