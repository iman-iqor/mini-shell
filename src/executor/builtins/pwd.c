/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:17 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 22:44:35 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*pwd;
	char	*cwd;

	pwd = get_env_value(g_general.env_list, "PWD");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		if (pwd)
			printf("%s\n", pwd);
		else if (g_general.old_pwd)
			printf("%s\n", g_general.old_pwd);
		g_general.exit_status = 0;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	g_general.exit_status = 0;
}
