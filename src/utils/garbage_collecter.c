#include"../../includes/minishell.h"


void	unlink_files(void)
{
	t_collector	*curr;

	curr = g_global_var.files;
	while (curr)
	{
		unlink((char *)curr->memory);
		curr = curr->next;
	}
}

t_collector	*init_garbage(void)
{
	return (NULL);
}

void	*gc_alloc(size_t size)
{
	void		*ptr;
	t_collector	*new_node;

	ptr = ft_calloc(size, 1);
	if (!ptr)
		return (NULL);
	new_node = (t_collector *)ft_calloc(sizeof(t_collector), 1);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->memory = ptr;
	new_node->next = g_global_var.garbage;
	g_global_var.garbage = new_node;
	return (ptr);
}

void	gc_free(t_collector **gc, void *ptr)
{
	t_collector	**curr;
	t_collector	*tmp;

	curr = gc;
	while (*curr)
	{
		if ((*curr)->memory == ptr)
		{
			tmp = *curr;
			*curr = (*curr)->next;
			free(tmp->memory);
			free(tmp);
			return ;
		}
		curr = &(*curr)->next;
	}
}

void	gc_clean(void)
{
	t_collector	*curr;
	t_collector	*tmp;

	curr = g_global_var.garbage;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->memory);
		free(tmp);
	}
	g_global_var.garbage = NULL;
	rl_clear_history();
	close(g_global_var.in);
	close(g_global_var.out);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
