/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:40:05 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 20:07:22 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execve(char *exact_path, t_list *list)
{
	env_list_to_array(g_general.env_list);
	execve(exact_path, list->argument, g_general.env_array);
	if (errno == EACCES)
	{
		write(2, "minishell: permission denied: ", 30);
		write(2, exact_path, strlen(exact_path));
		write(2, "\n", 1);
		imane_exit(126);
	}
	else if (errno == ENOENT)
	{
		write(2, "minishell: ", 12);
		write(2, exact_path, strlen(exact_path));
		write(2, " :No such file or directory", 28);
		write(2, "\n", 1);
		imane_exit(127);
	}
	else
	{
		perror("minishell");
		imane_exit(127);
	}
	return (0);
}
