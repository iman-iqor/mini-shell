/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:21:19 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/17 16:23:11 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char* ft_strndup(char* str,int n)
{
	int i;
	char* s;
	i = 0;
	
	s = ft_gc(n,'m');
	
	while( n >i)
	{
		s[i] = str[i];
		i++;
	}
	s[n] = 0;
	
	return s;
	
}



t_env *init_env_list(char **envp)
{
	t_env *head = NULL;
	t_env *node;
	char *equal;
	int i = 0;

	while (envp[i])
	{
		node = ft_gc(sizeof(t_env),'m');
		if (!node)
			return NULL;
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			node->key = strndup(envp[i], equal - envp[i]);
			node->value = ft_strdup(equal + 1);
		}
		else
		{
			node->key = strdup(envp[i]);
			node->value = NULL;
		}
		node->next = head;
		head = node;
		i++;
	}
	return head;
}

int	main(int argc,char** argv,char** env)
{
	// t_list list;

	// char *input;
	(void) argc;
	(void) argv;
	(void) env;
	

	// while (1)
	// {
	// 	input = readline("minishell> ");
	// 	if (input == NULL)
	// 		break ;
	// 	if (*input)
	// 		add_history(input);
	// 	list.argument = ft_split(input, ' ');
    //     exec_builtin(&list);

	// 	free(input);
	// }
	char* s = "imane";
	printf("%s\n",ft_strndup(s,3));
	return (0);
}


