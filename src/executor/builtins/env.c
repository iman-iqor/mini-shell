/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:02 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/10 21:54:47 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	t_env	*env;

	env = g_general.env_list;
	if (!get_envar("PATH"))
	{
		write(2, "env: No such file or directory\n", 32);
		g_general.exit_status = 127;
		return ; // <== IMPORTANT
	}
	while (env)
	{
		if (env->value)
		{
			ft_putstr(env->key);
			ft_putstr("=");
			ft_putstr(env->value);
			ft_putstr("\n");
		}
		env = env->next;
	}
	g_general.exit_status = 0;
}
