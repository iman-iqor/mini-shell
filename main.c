/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:21:19 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/18 23:04:46 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./no_int_main/includes/minishell.h"


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
t_env *ft_create_env_node(char* env)
{
	t_env *node;
	char* equal;

	node = ft_gc(sizeof(t_env),'m');
	if(!node)
		return NULL;
	equal = ft_strchr(env,'=');
	if(equal)
	{
		node->key = ft_strndup(env,equal - env);
		node->value = ft_strdup(equal+1);
	}
	else
	{
		node->key = ft_strdup(env);
		node->value = NULL;
	}
	node->next = NULL;
	return node;	
}
t_env* init_env_list(char** env)
{
	t_env *head = NULL;
	t_env *node;
	int i;
	i = 0;
	while(env[i])
	{
		node = ft_create_env_node(env[i]);
		node->next = head;
		head = node;
		i++;
	}
	return head;
}



//int main d imane
int	main(int argc,char** argv,char** env)
{
	// t_list list;
	t_env *my_env;

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
	my_env=init_env_list(env);
	printf("%s\n",my_env->value);
	return (0);
}


//
// int main()
// {
	
// }
