#include"../../includes/minishell.h"




//new variable
t_envp	*add_env_var(char *key, char *value, t_envp *prev)
{
	t_envp	*env;

	env = gc_alloc(sizeof(t_envp));
	if (env == NULL)
	{
		return (NULL);
	}
	env->exists = 1;
	env->key = key;
	env->value = value;
	env->prev = prev;
	env->next = NULL;
	return (env);
}
//add variable to the end
void	addback(t_envp *new)
{
	t_envp	*node;

	node = last_envar(g_global_var.env);
	if (node)
		node->next = new;
	else
		g_global_var.env = new;
}
//last var
t_envp	*last_envar(t_envp *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}
//create a node
t_envp	*create_env1(char **env, int i, t_envp *head)
{
	t_envp	*new;
	char	*key;
	char	*value;

	new = NULL;
	key = substr_char(env[i], '=');
	if (key == NULL)
		return (write(2, "malloc failed\n", 15), NULL);
	value = ft_strchr(env[i], '=');
	if (value)
		value++;
	else
		value = "";
	new = add_env_var(key, value, last_envar(head));
	if (new == NULL)
		return (write(2, "malloc failed\n", 15), NULL);
	addback(new);
	return (g_global_var.env);
}
//create env 
t_envp	*create_env(char **env)
{
	int		i;
	t_envp	*head;

	if (env == NULL)
		return (NULL);
	i = 0;
	head = NULL;
	while (env[i])
	{
		if (create_env1(env, i, g_global_var.env) == NULL)
			return (NULL);
		i++;
	}
	return (head);
}
