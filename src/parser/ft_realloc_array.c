/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:13:27 by mbenjbar          #+#    #+#             */
/*   Updated: 2025/05/06 19:14:54 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// func to add element to array and return the array
char	**ft_realloc_array(char **arr, char *new_str)
{
	int		len;
	int		i;
	char	**new_arr;

	len = 0;
	if (arr)
		while (arr[len])
			len++;
	new_arr = ft_gc(sizeof(char *) * (len + 2), 'm');
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[len] = ft_strdup(new_str);
	new_arr[len + 1] = NULL;
	free(arr);
	return (new_arr);
}
