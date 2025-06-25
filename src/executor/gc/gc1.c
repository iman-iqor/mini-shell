/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:03:58 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 19:03:55 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(t_gc *gc)
{
	t_gc	*next;

	next = NULL;
	while (gc)
	{
		next = gc->next;
		if (gc->type == GC_TEMPFILE)
			unlink((char *)gc->ptr);
		gc = next;
	}
}

void	*handle_m_flag(size_t n, t_gc **gc)
{
	void	*ptr;
	t_gc	*new;

	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	new = create(ptr);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	add(gc, new);
	return (ptr);
}

char	*handle_t_flag(char *filename, t_gc **gc)
{
	t_gc	*new;

	if (!filename)
		return (NULL);
	new = create(filename);
	if (!new)
	{
		free(filename);
		return (NULL);
	}
	new->type = GC_TEMPFILE;
	add(gc, new);
	return (filename);
}

/*
ptr: the pointer to free or unlink.
type: if it's a temp file or regular malloc.
next: points to the next GC node.
*/
void	*ft_gc(size_t n, char flag)
{
	static t_gc	*gc;
	char		*filename;

	g_general.gc = &gc;
	if (flag == 'm')
	{
		return (handle_m_flag(n, &gc));
	}
	else if (flag == 'f')
	{
		fr_ee(gc);
		gc = NULL;
	}
	else if (flag == 'p')
	{
		ft_unlink(gc);
	}
	else if (flag == 't')
	{
		filename = malloc(n);
		return (handle_t_flag(filename, &gc));
	}
	return (NULL);
}
