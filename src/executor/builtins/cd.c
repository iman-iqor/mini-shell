/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:52:56 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 22:27:56 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(int code)
{
	if (code == 1)
		write(2, "cd: HOME not set\n", 18);
	else if (code == 0)
		write(2, "cd : too many arguments\n", 24);
	else if (code == 2)
		perror("cd");
	g_general.exit_status = 1;
}

t_env	*get_envar(char *key)
{
	t_env	*node;

	node = g_general.env_list;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

int	if_else_of_cd(char **path, t_env *home, char **p)
{
	if (path && path[0] && path[0][0] == 0)
		return (g_general.exit_status = 0, 1);
	else if (path && path[0] && path[1])
		return (cd_error(0), 1);
	if ((!path || !path[0]) && home)
		*p = home->value;
	else if (path)
		*p = *path;
	if (*p && chdir(*p))
		return (cd_error(2), 1);
	if (!*p)
		return (cd_error(1), 1);
	return (0);
}

void	update_pwd(void)
{
	char	*current_directory;
	t_env	*pwd;

	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		write(2, "cd: error retrieving current directory: getcwd: cannot ", 56);
		write(2, "access parent directories: No such file or directory\n", 54);
		g_general.exit_status = 0;
		return ;
	}
	pwd = get_envar("PWD");
	if (pwd)
	{
		pwd->value = ft_gc(ft_strlen(current_directory) + 1, 'm');
		ft_strcpy(pwd->value, current_directory);
	}
	free(current_directory);
}

void	cd(char **path)
{
	t_env	*home;
	t_gc	*new;
	char	*p;
	char	*cwd;

	home = get_envar("HOME");
	p = NULL;
	if (if_else_of_cd(path, home, &p))
		return ;
	update_pwd();
	if (g_general.exit_status == 0)
		return ;
	g_general.old_pwd = getcwd(NULL, 0);
	new = create(g_general.old_pwd);
	if (new == NULL)
		imane_exit(1);
	add(g_general.gc, new);
	g_general.exit_status = 0;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		write(2, "cd: error retrieving current directory: getcwd: cannot ", 56);
		write(2, "access parent directories: No such file or directory\n", 54);
	}
	free(cwd);
}
