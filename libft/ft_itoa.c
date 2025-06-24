/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:18:35 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/24 23:04:21 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	countlen(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	checksigne(int *n, size_t *len)
{
	if (*n < 0)
	{
		(*len)++;
	}
}

char	*implement(char *str, size_t len, int n)
{
	str[len] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n && len > 0)
	{
		str[--len] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = 0;
	checksigne(&n, &len);
	len += countlen(n);
	str = ft_gc(len + 1, 'm');
	if (!str)
		return (NULL);
	str = implement(str, len, n);
	return (str);
}
