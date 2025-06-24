/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:36:40 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 18:36:43 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing_var(t_env *node, char *value, int mode)
{
	char	*joined;

	if (!value)
		return ;
	if (mode == 2)
	{
		joined = ft_strjoin(node->value ? node->value : "", value);
		node->value = joined;
	}
	else
		node->value = value;
}
