/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:23:31 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/14 10:59:32 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>
#include "../libft/libft.h"


typedef struct s_list
{
	char				**argument;
	
}						t_list;

int		ft_strcmp(char *s1, char *s2);
void	exec_builtin(t_list *list);
void	echo(char **list);
int		is_flag(char *str);
int		ft_countword(const char *str, char c)

#endif