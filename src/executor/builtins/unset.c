/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:37 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 18:04:42 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
First character must be a letter or underscore _.

Following characters must be alphanumeric or _.

Ignores leading whitespace.
*/
int	is_valid_unset(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
		return (0);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
Traverses the linked list.

If it finds a node matching the key, it adjusts pointers to unlink it:

If it's not the first node: connect prev and next.

If it's the first node: update g_general.env_list
*/
void	unset_var(char *key)
{
	t_env	*curr;

	curr = g_general.env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (curr->prev)
			{
				curr->prev->next = curr->next;
				if (curr->next)
					curr->next->prev = curr->prev;
			}
			else
			{
				curr = curr->next;
				curr->prev = NULL;
				g_general.env_list = curr;
			}
			break ;
		}
		curr = curr->next;
	}
}

void	handle_unset_error(char *arg)
{
	write(2, "unset: `", 8);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
}

void	print_unset_error(char *arg)
{
	if (ft_strchr(arg, '!'))
		write(2, "minishel:event not found\n", 25);
}

/*
Checks if variable names are valid.

Skips invalid ones and prints an error.

Deletes the node from the linked list if valid.

Sets the proper g_general.exit_status.
*/
void	unset(char **list)
{
	int	i;
	int	flag;

	if (!list || !list[0])
	{
		g_general.exit_status = 0;
		return ;
	}
	i = 0;
	flag = 0;
	while (list[i])
	{
		if (!is_valid_unset(list[i]))
		{
			print_unset_error(list[i]);
			flag = 0;
		}
		else
			unset_var(list[i]);
		i++;
	}
	if (flag)
		g_general.exit_status = 2;
	else
		g_general.exit_status = 0;
}
