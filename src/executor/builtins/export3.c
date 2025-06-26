/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:14 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/26 14:41:53 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_envar(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	addback(t_env *new_node)
{
	t_env	*tmp;

	tmp = g_general.env_list;
	if (!tmp)
	{
		g_general.env_list = new_node;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_env	*get_envar_with_passing_env_list(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	get_key_and_value(char *str, char **key, char **value)
{
	char	*plus_equal;
	char	*equal;

	plus_equal = ft_strnstr(str, "+=", ft_strlen(str));
	equal = ft_strchr(str, '=');
	if (plus_equal)
	{
		*key = ft_substr(str, 0, plus_equal - str);
		*value = ft_strdup(plus_equal + 2);
		return (2);
	}
	else if (equal)
	{
		*key = ft_substr(str, 0, equal - str);
		*value = ft_strdup(equal + 1);
		return (1);
	}
	else
	{
		*key = ft_strdup(str);
		*value = NULL;
		return (0);
	}
}

/*
Creates a new environment variable node with given key, value, 
and previous node pointer.
*/
t_env	*add_env_var(char *key, char *value, t_env *prev)
{
	t_env	*env;

	env = ft_gc(sizeof(t_env), 'm');
	if (env)
	{
		env->key = key;
		env->value = value;
		env->prev = prev;
		env->next = NULL;
	}
	return (env);
}
