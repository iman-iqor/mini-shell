/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:23:31 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/15 21:07:38 by imiqor           ###   ########.fr       */
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

// typedef struct s_global
// {
// 	int					exit_status;
// 	int					i;
// 	int					in;
// 	pid_t				pid;
// 	int					out;
// 	t_envp				*env;
// 	t_collector			*garbage;
// 	t_collector			*files;
// 	int					stop;
// }						t_global;

// t_global	g_global_var;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				exists;
	struct s_env	*next;
	struct s_env	*prev;
}					t_envp;

typedef struct s_var
{
	int i;
}				t_var;

typedef struct s_list
{
	char				**argument;
	
}						t_list;

int		ft_strcmp(char *s1, char *s2);
void	exec_builtin(t_list *list);
void	echo(char **list);
int		is_flag(char *str);
int	ft_countword(const char *str, char c);

#endif