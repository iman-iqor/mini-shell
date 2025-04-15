/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iman_sb3a.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:04:24 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/15 21:36:03 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAN_SB3A_H
# define IMAN_SB3A_H
# include <stdio.h>
# include <stdlib.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;
#endif