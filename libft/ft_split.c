/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:54:40 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 17:22:56 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char *str, char c)
{
	int	countword;
	int	isinword;

	countword = 0;
	isinword = 0;
	while (*str)
	{
		isinword = 0;
		while (*str && *str == c)
		{
			str++;
		}
		while (*str && *str != c)
		{
			if (!isinword)
			{
				isinword = 1;
				countword += 1;
			}
			str++;
		}
	}
	return (countword);
}

static char	*ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char		**arr;
	char	*start;
	int			i;

	if (!s)
		return (NULL);
	arr = ft_calloc((ft_countword(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (s > start)
		{
			arr[i] = ft_substr(start, 0, s - start);
			if (!arr[i++])
				return (ft_free(arr), NULL);
		}
	}
	return (arr);
}
