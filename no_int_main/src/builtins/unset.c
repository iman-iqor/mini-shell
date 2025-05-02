#include "../../includes/minishell.h"
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
	t_env *curr ;
    curr = g_general.env_list;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				g_general.env_list = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			// No need to free `curr` or its contents — GC handles it.
			return;
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
		write(2, "unset: not enough arguments", 28);
		g_general.exit_status = 1;
		return ;
	}
	i = 0;
	flag = 0;
	while (list[i])
	{
		if (!is_valid_unset(list[i]))
		{
			handle_unset_error(list[i]);
			flag = 1;
		}
		else
			unset_var(list[i]);
		i++;
	}
	g_general.exit_status = (flag ? 2 : 0);
}

