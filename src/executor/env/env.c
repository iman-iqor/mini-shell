/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:41 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 19:01:44 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_create_env_node(char *env)
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

/*
Loops over all strings in env

Uses	ft_create_env_node(void) to convert each

Links them as prev / next in the list

Sets g_general.env_list to the head
*/
t_env	*init_env_list(char **env)
{
	int		i;
	t_env	*head;
	t_env	*node;
	t_env	*last;

	head = NULL;
	last = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_create_env_node(env[i]);
		if (node == NULL)
			imane_exit(1);
		node->prev = NULL;
		if (last == NULL)
			head = node;
		else
		{
			last->next = node;
			node->prev = last;
		}
		last = node;
		i++;
	}
	return (g_general.env_list = head, head);
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

/*
Purpose:
Combines key and value into a "key=value" string.

Used in:
When creating char **envp array for execution (execve).
*/
char	*ft_join_key_value(char *key, char *value)
{
	int		len;
	char	*joined;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	joined = ft_gc(len, 'm');
	if (!joined)
		return (NULL);
	ft_strcpy(joined, key);
	ft_strcat(joined, "=");
	ft_strcat(joined, value);
	return (joined);
}

/*
Calls	env_len(void) to know how much space to allocate

Loops through the list

If node has a value → uses ft_join_key_value()

If no value → copies only the key

Adds NULL terminator at the end

Saves the array in g_general.env_array
*/
char	**env_list_to_array(t_env *env_list)
{
	char	**envp;
	int		i;
	int		count;

	count = env_len(env_list);
	envp = ft_gc(sizeof(char *) * (count + 1), 'm');
	i = 0;
	while (env_list)
	{
		if (env_list->value)
			envp[i++] = ft_join_key_value(env_list->key, env_list->value);
		else
			envp[i++] = ft_strdup(env_list->key);
		env_list = env_list->next;
	}
	envp[i] = NULL;
	g_general.env_array = envp;
	return (envp);
}
