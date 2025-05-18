#include "../includes/minishell.h"


void    sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        exit(130);
    }
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}



int	do_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return -1;
	}
	if (pid == 0)
	{
		handle_heredoc_signals();
		close(pipefd[0]);
		while (1)
		{
			line = readline(">");
			if (!line || !ft_strcmp(line, delimiter))
			{
				free(line);
				close(pipefd[1]);
				
				break ; //i was doing break instead of exit(0);
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
			
		}
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	restore_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return -1; // heredoc was interrupted by Ctrl+C
	}
	return (pipefd[0]);
}

int	heredoc(t_list *list)
{
	int	fd;

	fd = -1;
	// i created tmp to not broke the file's list
	t_file *tmp = list->input_file;
	while (tmp)
	{	
		if (fd != -1)// Close previous file descriptor before opening a new one
			{
				close(fd); 
				fd = -1;
			}
		if (tmp->flag == 1)
		{
			
			fd = do_heredoc(tmp->file_name);
			if (fd == -1)
				return (-1); 
		}
		else
		{
			if (fd != -1)
				close(fd);
			fd = open(tmp->file_name, O_RDONLY);
			if (fd == -1)
			{
				perror(tmp->file_name);
				return (-1);
			}
		}
		
		tmp = tmp->next;
		// We don't exit the loop - we want to process all input files
        // The last one will be the one that remains open and is used
        // for input to the command, just like in Bash
	}
	list->fd = fd;
	return 0;
}
