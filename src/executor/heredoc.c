#include "../includes/minishell.h"

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_general.exit_status = 130;
		imane_exit(130); // i need here to free the memory and exit with 130 not just exit
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
	char *gc_path;

	while (1)
	{
		if (i > 1000)
			return (NULL);

		num = ft_itoa(i++);
		name = ft_strjoin("heredoc_", num);

		path = ft_strjoin("/tmp/", name);

		if (!path)
			return NULL;

		if (access(path, F_OK) != 0)
		{
			// Register with GC and return
			gc_path = ft_gc(strlen(path) + 1, 't');

			strcpy(gc_path, path);
			return gc_path;
		}
	}
}
void imane_exit(int status)
{
	ft_gc(0, 'f');

	exit(status);
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
		imane_exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}
	if (pid == 0)
	{
		set_signals_child();

		handle_heredoc_signals();
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				imane_exit(0);
			}
			if (!ft_strcmp(line, tmp->file_name))
			{
				free(line);
				imane_exit(0);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		close(fd);
		unlink(file);
		return (-130);
	}

	tmp->file_name = ft_strdup(file);
	return (fd);
}

int heredoc(t_list *list, t_file *tmp)
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
	if(fd==-130)
	{
		g_general.exit_status=130;
		return -1;
	}
	list->fd = fd; // Store the final file descriptor in the list
	return (0);
}