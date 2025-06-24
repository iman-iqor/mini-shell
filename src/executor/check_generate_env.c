/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_generate_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:37:31 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 19:56:03 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_back_env(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

int	check_if_there_is_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_there_is_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

t_env	*generate_minimal_env(void)
{
	t_generate_minimal_env	var;

	var.env_list = NULL;
	if (getcwd(var.cwd, sizeof(var.cwd)))
	{
		var.pwd_str = ft_strjoin("PWD=", var.cwd);
		var.pwd_node = ft_create_env_node(var.pwd_str);
		add_back_env(&var.env_list, var.pwd_node);
	}
	var.shlvl = ft_itoa(1);
	if (var.shlvl)
	{
		var.shlvl_str = ft_strjoin("SHLVL=", var.shlvl);
		var.shlvl_node = ft_create_env_node(var.shlvl_str);
		add_back_env(&var.env_list, var.shlvl_node);
	}
	var._ = ft_strdup("_=./minishell");
	var._node = ft_create_env_node(var._);
	add_back_env(&var.env_list, var._node);
	return (var.env_list);
}

void	check_env(char **env, t_env **my_env_list)
{
	if (env && env[0])
	{
		*my_env_list = init_env_list(env);
		if (!check_if_there_is_pwd(env))
		{
			g_general.pwd_node = ft_create_env_node(g_general.pwdd);
			add_back_env(my_env_list, g_general.pwd_node);
		}
	}
	else
	{
		*my_env_list = generate_minimal_env();
		g_general.env_list = *my_env_list;
	}
}
