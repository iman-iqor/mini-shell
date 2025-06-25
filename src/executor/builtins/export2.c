/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:12 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 17:56:46 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Parses the key and value from the input string (key=value or key+=value).

Checks if variable already exists; updates if yes, creates new otherwise.
*/
void	export_logique(char **list)
{
	t_env	*node;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		mode;

	mode = get_key_and_value(list[0], &key, &value);
	if (!key)
		return ;
	node = get_envar_with_passing_env_list(g_general.env_list, key);
	if (node)
		update_existing_var(node, value, mode);
	else
	{
		new_node = add_env_var(key, value, last_envar(g_general.env_list));
		if (new_node)
			addback(new_node);
	}
}

void	print_env_var(t_env *env)
{
	write(1, "declare -x ", 11);
	write(1, env->key, ft_strlen(env->key));
	if (env->value)
	{
		write(1, "=\"", 2);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	sort_ascii(char **arr)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	while (arr && arr[i])
	{
		j = 0;
		while (arr[j + 1])
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_sorted(char **keys, t_env *env_list)
{
	int		i;
	t_env	*var;

	i = 0;
	while (keys && keys[i])
	{
		var = get_envar_with_passing_env_list(env_list, keys[i]);
		print_env_var(var);
		i++;
	}
}

void	export_no_args(void)
{
	char	**keys;

	keys = get_env_keys(g_general.env_list);
	sort_ascii(keys);
	print_export_sorted(keys, g_general.env_list);
}
