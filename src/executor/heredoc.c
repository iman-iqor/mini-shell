#include "../includes/minishell.h"

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130); // i need here to free the memory and exit not just exit
	}
}

void handle_heredoc_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

char *get_tmp_file(void)
{
	static int i = 0;
	char *num;
	char *name;
	char *path;

	while (1)
	{
		if (i > 1000)
			return (NULL);
		num = ft_itoa(i++);
		name = ft_strjoin("heredoc_", num);
		free(num);
		path = ft_strjoin("/tmp/", name);
		if (access(path, F_OK) != 0)
			return (path);
	}
}
int do_heredoc(t_file *tmp)
{
	pid_t pid;
	int status;
	char *line;
	int fd;
	char *file;

	file = get_tmp_file();
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		handle_heredoc_signals();
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				exit(0);
			}
			if (!ft_strcmp(line, tmp->file_name))
			{
				free(line);
				exit(0);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		// close(fd);
		// exit(0);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		close(fd);
		return (-1);
	}
	free(tmp->file_name);
	tmp->file_name = ft_strdup(file);
	return (fd);
}

int heredoc(t_list *list,t_file *tmp)
{
	int fd;

	fd = -1;
	
	fd = do_heredoc(tmp);
	if (fd == -1)
	{
		return (-1);
	}
	if (fd == -2)
		return (-1);

	list->fd = fd; // Store the final file descriptor in the list
	return (0);
}
