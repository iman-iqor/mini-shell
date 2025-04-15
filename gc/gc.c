/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:03:58 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/15 21:36:07 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iman_sb3a.h"

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

void	*ft_gc(size_t n, char flag)
{
	static t_gc	*gc;
	void		*ptr;
	t_gc		*new;

	if (flag == 'm')
	{
		ptr = malloc(n);
		if (ptr == NULL)
			return (NULL);
		new = create(ptr);
		if (new == NULL)
		{
			free(ptr);
			return (NULL);
		}
		add(&gc, new);
		return (ptr);
	}
	else if (flag == 'f')
		fr_ee(gc);
	return (NULL);
}
