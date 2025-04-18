/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:06:32 by imiqor            #+#    #+#             */
/*   Updated: 2024/11/15 01:24:02 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str2;
	int		len;
	int		i;

	len = ft_strlen(s1);
	str2 = malloc(len + 1);
	if (!str2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str2[i] = s1[i];
		i++;
	}
	str2[i] = 0;
	return (str2);
}
