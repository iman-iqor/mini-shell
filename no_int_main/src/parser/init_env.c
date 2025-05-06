/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:54:28 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/05 22:44:58 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static t_env	*ft_create_simo_node(char *env)
{
	t_env	*node;
	char	*equal;

	node = ft_gc(sizeof(t_env), 'm');
	if (!node)
		return (NULL);
	equal = ft_strchr(env, '=');
	if (equal)
	{
		node->key = ft_strndup(env, equal - env);
		node->value = ft_strdup(equal + 1);
	}
	else
	{
		node->key = ft_strdup(env);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*node;
	t_env	*last;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_create_simo_node(env[i]);
		
		if (last == NULL)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
}
