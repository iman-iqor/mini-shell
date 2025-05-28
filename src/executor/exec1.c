#include "../includes/minishell.h"


// void	pwd(void);

void exec_builtin(t_list *list)
{
	if (!list || !list->argument || !list->argument[0])
		return;

	if (ft_strcmp("echo", list->argument[0]) == 0)
		echo(list->argument + 1);
	else if (ft_strcmp("cd", list->argument[0]) == 0)
		cd(list->argument + 1);
	else if (ft_strcmp("env", list->argument[0]) == 0)
		env();
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


void	input_no_output(t_list *list)
{
	int	fd_in;
	t_file	*tmp;
	tmp = list->input_file;
	fd_in = -1;
	while(tmp)
	{
		if (fd_in != -1)
			close(fd_in);
		if (tmp->flag)
		{
			if (heredoc(list,tmp) == -1)
				return ;
			// tmp->file_name = list->input_file->file_name;
		}
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
			perror(tmp->file_name);
			list->error_flag = 1;
			return ;
		}
		tmp = tmp->next;
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}


void	input_output(t_list *list)
{
	input_no_output(list);
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
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
	}
	signal(SIGINT, h);
}


void exec_externals(t_list *list)
{
	pid_t pid;

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
		execute_command(list);
	}
	else // parent process
	{
		wait_and_update_status(pid);
	}
}

void	ft_redirect_and_execute(t_list *list)
{
	if (list->input_file && !list->output_file)
		input_no_output(list);
	else if (!list->input_file && list->output_file)
		output_no_input(list);
	else if (list->input_file && list->output_file)
		input_output(list);
	if (list->error_flag)
		return; // Skip execution due to redirection error
	if (list->argument)
	{
		if (is_builtin(list->argument[0]))
			exec_builtin(list);
		else
			exec_externals(list);
	}
}
void	execute_builtins_and_externals(t_list *list)
{
	if (list == NULL || list->argument == NULL)
		return;
	if (is_builtin(list->argument[0]))
		exec_builtin(list);
	else
		exec_externals(list);
}
int	ft_exec_single_command(t_list *list)
{
	if (!list || list->next)
		return (0);
	
	if (list && list->next == NULL)
	{
		int(saved_stdout), (saved_stdin);
		saved_stdout = dup(1);
		saved_stdin = dup(0);
		if (list->input_file || list->output_file)
			ft_redirect_and_execute(list);
		else
			execute_builtins_and_externals(list);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	return (0);
}




void	ft_exec(t_list *list)
{
	
	if (list && !list->next)
	{
		ft_exec_single_command(list);
		return ;
	}
	else if(list && list->next)
	{
		
		ft_exec_piped_commands(list);
		return;
	}
}