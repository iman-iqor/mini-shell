/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:03:58 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/10 21:53:45 by imiqor           ###   ########.fr       */
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

void *handle_m_flag(size_t n, t_gc **gc)
{
	void *ptr;
	t_gc *new;

	ptr = malloc(n);
	if (!ptr)
		return NULL;
	new = create(ptr);
	if (!new)
	{
		free(ptr);
		return NULL;
	}
	add(gc, new);
	return ptr;
}

char *handle_t_flag(char *filename, t_gc **gc)
{
	t_gc *new;

	if (!filename)
		return NULL;
	new = create(filename);
	if (!new)
	{
		free(filename);
		return NULL;
	}
	new->type = GC_TEMPFILE;
	add(gc, new);
	return filename;
}

void	*ft_gc(size_t n, char flag)
{
	static t_gc	*gc;
	char *filename;

	g_general.gc = &gc;
	if (flag == 'm')
	{
		
		return handle_m_flag(n, &gc);
	}
	else if (flag == 'f'){
		fr_ee(gc);gc=NULL;}
	else if(flag=='p')
	{
		ft_unlink(gc);
	}
	else if (flag == 't') {  // Temp file registration
		filename = malloc(n);
		return handle_t_flag(filename, &gc);
	}
	return (NULL);
}
