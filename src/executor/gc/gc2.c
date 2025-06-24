/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:03:58 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 22:46:01 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add(t_gc **gc, t_gc *new)
{
	t_gc	*ptr;

	if (new)
	{
		ptr = *gc;
		while (ptr && ptr->next)
		{
			ptr = ptr->next;
		}
		if (ptr)
		{
			ptr->next = new;
		}
		else
		{
			*gc = new;
		}
	}
}

t_gc	*create(void *ptr)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
	{
		return (NULL);
	}
	gc->ptr = ptr;
	gc->type = 0;
	gc->next = NULL;
	return (gc);
}

void	fr_ee(t_gc *gc)
{
	t_gc	*next;

	next = NULL;
	while (gc)
	{
		next = gc->next;
		free(gc->ptr);
		free(gc);
		gc = next;
	}
}
