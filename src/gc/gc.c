/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:03:58 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/01 17:44:25 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
void	ft_unlink(t_gc *gc)
{
	t_gc	*next;

	next = NULL;
	while (gc)
	{
		next = gc->next;
		if (gc->type == GC_TEMPFILE) 
			unlink((char *)gc->ptr);  // Delete temp file
		
		gc = next;
	}
}

void	*ft_gc(size_t n, char flag)
{
	static t_gc	*gc;
	void		*ptr;
	t_gc		*new;

	g_general.gc = &gc;
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
	else if (flag == 'f'){
		fr_ee(gc);gc=NULL;}
	else if(flag=='p')
	{
		ft_unlink(gc);
	}
	else if (flag == 't') {  // Temp file registration
		char *filename = malloc(n);
		if (!filename) return NULL;
		new = create(filename);
		if (!new) {
			free(filename);
			return NULL;
		}
		new->type = GC_TEMPFILE;
		add(&gc, new);
		return filename;
	}
	return (NULL);
}
