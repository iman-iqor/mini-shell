#include "../../includes/minishell.h"

int	list_len(t_list *list)
{
	int i;
    t_list *tmp;
    tmp = list;

	i = 0;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}