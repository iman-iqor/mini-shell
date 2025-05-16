#include "../includes/minishell.h"
#define TMP_HEREDOC_FILE "/tmp/.heredoc_temp"

void	child_heredoc(char *delim)
{
	char *line;
	int fd = open(TMP_HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	signal(SIGINT, SIG_DFL); // Restore default CTRL+C behavior

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delim) == 0)
			break;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

int	heredoc(t_list *list)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
		child_heredoc(list->input_file[0]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		// Ctrl+C pressed, cleanup
		unlink(TMP_HEREDOC_FILE);
		return (-1);
	}
	return (open(TMP_HEREDOC_FILE, O_RDONLY));
}