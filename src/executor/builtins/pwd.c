/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:17 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/10 21:53:18 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void	pwd(void)
{
	char *cwd ; // will malloc the exact needed space
    cwd = getcwd(NULL, 0);

	if (cwd == NULL)//in the case where the path could be deleted
	{
		if(g_general.old_pwd)
			printf("%s\n", g_general.old_pwd);
		g_general.exit_status = 0;
		return;
	}
    printf("%s\n", cwd);
    free(cwd);
	// free(g_general.old_pwd);
	g_general.exit_status = 0;
}
