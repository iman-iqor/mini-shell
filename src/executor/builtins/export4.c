#include "minishell.h"

void	update_existing_var(t_env *node, char *value, int mode)
{
	char	*joined;

	if (!value)
		return ;
	if (mode == 2)
	{
		joined = ft_strjoin(node->value ? node->value : "", value);
		node->value = joined;
	}
	else
		node->value = value;
}