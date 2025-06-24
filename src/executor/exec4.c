/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:48 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 22:23:31 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_no_input_pipe(t_list *list)
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
			output_no_input_error(tmp, list);
			exit(1);
		}
		dup2(fd_out, STDOUT_FILENO);
		tmp = tmp->next;
	}
	close(fd_out);
}
