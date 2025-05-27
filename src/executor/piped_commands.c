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
	else {
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
	int	fd_in;
	t_file	*tmp;
	tmp = list->input_file;
	fd_in = -1;
	while(tmp)
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
// int execute_command(t_list *list)
// {
// 	char *exact_path;
// 	if (list && list->argument && ft_strlen(list->argument[0]) == 0)
// 	{
// 		write(2, "minishell: empty command\n", 26);
// 		exit(127);
// 	}
// 	if (open(list->argument[0], __O_DIRECTORY) != -1)
// 	{

// 		write(2, list->argument[0], strlen(list->argument[0]));
// 		write(2, ": is a directory\n", 17);
// 		exit(126);
// 	}
// 	if (is_builtin(list->argument[0]))
// 	{
// 		exec_builtin(list);
// 		exit(g_general.exit_status); // Important to exit after builtin
// 	}
// 	else
// 	{
// 		exact_path = check_path(g_general.env_array, list);
// 		ft_execve(exact_path, list);
// 	}

	
// 	return (0);
// }
void	handle_child_process(t_list *list, t_exec_data *d)
{
	set_signals_child();

	if (list->input_file)
		input_no_output_of_pipe(list);  
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
	t_list *tmp = list;
	

	while(tmp)
	{
		
		if(tmp->input_file && tmp->input_file->flag)
		{
			if (heredoc(tmp,tmp->input_file) == -1)
				return ;
		}
		tmp = tmp->next;
	}
	// Check for any heredoc errors
    t_list *tmpp = list;
    while(tmpp) {
        if(tmpp->error_flag) {
            g_general.exit_status = 1;
            return;
        }
        tmpp = tmpp->next;
    }

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
