/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:37 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/15 18:33:33 by mbenjbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_unset(char *str)
{
    int i = 0;

    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
        return (0);
    while (str[i])
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}
void	unset_var(char *key)
{
	t_env *curr;

	curr = g_general.env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (curr->prev)
			{
				curr->prev->next = curr->next;
				if (curr->next)
					curr->next->prev=curr->prev;
			}
			else {
				curr = curr->next;
				curr->prev=NULL;
				g_general.env_list = curr;
			}
			
			break;
		}
		curr = curr->next;
	}
}


void	handle_unset_error(char *arg)
{
	write(2, "unset: `", 8);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
}

void	unset(char **list)
{
	int	i;
	int	flag;

	if (!list || !list[0])
	{
		g_general.exit_status = 0;//that s how the bash treats this case 
		return ;
	}
	i = 0;
	flag = 0;
	while (list[i])
	{
		if (!is_valid_unset(list[i]))
		{
			if(ft_strchr(list[i],'!'))
                write(2,"minishel:event not found\n",25);
                
			// handle_unset_error(list[i]);//this is how bash behave exit with 0 in this case and does not complain
			flag = 0;
		}
		else
			unset_var(list[i]);
		i++;
	}
	g_general.exit_status = (flag ? 2 : 0);
}
