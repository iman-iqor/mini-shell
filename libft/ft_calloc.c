/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:38:53 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 22:58:21 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;
	size_t	p;

	p = count * size;
	if (size && p / size != count)
		return (NULL);
	s = ft_gc(count * size, 'm');
	if (!s)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}
