/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:09 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 17:54:44 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Collects all environment variable keys from the linked list into a
NULL-terminated array of strings.
Used for sorting and printing.
*/
char	**get_env_keys(t_env *env_list)
{
	int		size;
	t_env	*tmp;
	char	**keys;
	int		i;

	size = 0;
	tmp = env_list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	keys = ft_gc(sizeof(char *) * (size + 1), 'm');
	if (!keys)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		keys[i] = ft_strdup(tmp->key);
		tmp = tmp->next;
		i++;
	}
	keys[size] = NULL;
	return (keys);
}

/*
Checks if the input string is a valid environment variable identifier for export.
Valid keys start with a letter or _, and may contain letters, digits, _.
 Handles += syntax.
*/
int	is_valid(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '=')
		i += 2;
	else if (str[i] == '=')
		i += 1;
	return (1);
}

void	handle_exit_status(int flag)
{
	if (flag)
		g_general.exit_status = 1;
	else
		g_general.exit_status = 0;
}

int	invalid_identifier_error(char *list)
{
	int	flag;

	flag = 0;
	if (ft_strchr(list, '!'))
	{
		write(2, "minishel:event not found\n", 25);
		flag = 0;
	}
	else
	{
		write(2, "export: `", 9);
		write(2, list, ft_strlen(list));
		write(2, "': not a valid identifier\n", 27);
		flag = 1;
	}
	return (flag);
}

/*
If no arguments, prints current env variables sorted.

Otherwise, validates each argument and calls export logic or prints errors.

Sets exit status accordingly.
*/
void	export(char **list)
{
	int	i;
	int	flag;

	if (!list || !list[0])
	{
		export_no_args();
		g_general.exit_status = 0;
		return ;
	}
	i = 0;
	flag = 0;
	while (list[i])
	{
		if (!is_valid(list[i]))
			flag = invalid_identifier_error(list[i]);
		else
			export_logique(&list[i]);
		i++;
	}
	handle_exit_status(flag);
}
