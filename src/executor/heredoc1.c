/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:59 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 18:10:45 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_tmp_file(void)
{
	static int	i;
	t_tmp_vars	var;

	while (1)
	{
		if (i > 1000)
			return (NULL);
		var.num = ft_itoa(i++);
		var.name = ft_strjoin("heredoc_", var.num);
		var.path = ft_strjoin("/tmp/", var.name);
		if (!var.num || !var.name || !var.path)
			return (NULL);
		if (access(var.path, F_OK) != 0)
		{
			var.gc_path = ft_gc(strlen(var.path) + 1, 't');
			if (!var.gc_path)
				return (NULL);
			ft_strcpy(var.gc_path, var.path);
			return (var.gc_path);
		}
	}
}

void	imane_exit(int status)
{
	ft_gc(0, 'f');
	exit(status);
}

void	heredoc_child(t_file *tmp, int fd)
{
	char	*line;
	int		i;
	char	*line2;

	handle_heredoc_signals();
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, tmp->file_name))
		{
			free(line);
			imane_exit(0);
		}
		line2 = ft_strdup("");
		i = 0;
		while (line[i])
			line2 = process_of_expanding(line, &i, line2, 0);
		free(line);
		write(fd, line2, ft_strlen(line2));
		write(fd, "\n", 1);
	}
}

int	do_heredoc(t_file *tmp)
{
	pid_t	pid;
	int		status;
	int		fd;
	char	*file;

	file = get_tmp_file();
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		g_general.exit_status = 1;
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc_child(tmp, fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, h);
	if (WEXITSTATUS(status) == 130)
		return (close(fd), unlink(file), -130);
	tmp->file_name = ft_strdup(file);
	return (fd);
}

int	heredoc(t_list *list, t_file *tmp)
{
	int	fd;

	g_general.heredoc_interupt = 0;
	fd = -1;
	fd = do_heredoc(tmp);
	if (fd == -1)
	{
		g_general.exit_status=1;
		return (-1);
	}
	if (fd == -2)
	{
		g_general.exit_status=1;
		return (-1);
	
	}
	if (fd == -130)
	{
		g_general.heredoc_interupt = 1;
		g_general.exit_status = 130;
		return (-1);
	}
	list->fd = fd;
	return (0);
}
