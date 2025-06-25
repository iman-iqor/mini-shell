/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:48 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 21:35:37 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtins_and_externals(t_list *list)
{
	if (list == NULL || list->argument == NULL)
		return ;
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
		g_general.out = dup(1);
		g_general.in = dup(0);
		if (list->input_file || list->output_file)
			ft_redirect_and_execute(list);
		else
			execute_builtins_and_externals(list);
		dup2(g_general.in, STDIN_FILENO);
		dup2(g_general.out, STDOUT_FILENO);
		close(g_general.in);
		close(g_general.out);
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
	else if (list && list->next)
	{
		ft_exec_piped_commands(list);
		return ;
	}
	ft_gc(0, 'p');
}
