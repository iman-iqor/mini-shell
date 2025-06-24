/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:42:51 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 18:42:58 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_add_file(t_list *cmds, char *new_str, int flag, char c)
{
	t_file	*new;
	t_file	*tmp;

	new = ft_gc(sizeof(t_file), 'm');
	new->file_name = ft_strdup(new_str);
	new->flag = flag;
	new->next = NULL;
	if (c == 'i')
		tmp = cmds->input_file;
	else
		tmp = cmds->output_file;
	if (tmp == NULL)
	{
		if (c == 'i')
			cmds->input_file = new;
		else
			cmds->output_file = new;
		return (cmds);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (cmds);
}
