/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:48 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/17 17:27:48 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtins_and_externals(t_list *list)
{
	if (list == NULL || list->argument == NULL)
		return ;
	if (is_builtin(list->argument[0]))
		exec_builtin(list);
	else
		exec_externals(list);
}
int	ft_exec_single_command(t_list *list, t_env *env)
{
	if (!list || list->next)
		return (0);
	if (list && list->next == NULL)
	{
		int(saved_stdout), (saved_stdin);
		saved_stdout = dup(1);
		saved_stdin = dup(0);
		if (list->input_file || list->output_file)
			ft_redirect_and_execute(list, env);
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

void	ft_exec(t_list *list, t_env *env)
{
	
	if (list && !list->next)
	{
		ft_exec_single_command(list, env);
		return ;
	}
	else if (list && list->next)
	{
		ft_exec_piped_commands(list, env);
		return ;
	}
	ft_gc(0, 'p');
}
