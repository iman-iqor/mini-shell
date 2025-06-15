#include "../includes/minishell.h"
void	add_back_env(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

int	check_if_there_is_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
int	check_if_there_is_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}


t_env	*generate_minimal_env(void)
{
	t_generate_minimal_env var;
	
	var.env_list = NULL;
	if (getcwd(var.cwd, sizeof(var.cwd)))
	{
		var.pwd_str = ft_strjoin("PWD=", var.cwd);
		var.pwd_node = ft_create_env_node(var.pwd_str);
		add_back_env(&var.env_list, var.pwd_node);
	}
	var.shlvl = ft_itoa(1);
	if (var.shlvl)
	{
		var.shlvl_str = ft_strjoin("SHLVL=", var.shlvl);
		var.shlvl_node = ft_create_env_node(var.shlvl_str);
		add_back_env(&var.env_list, var.shlvl_node);
	}
	var.path_str = ft_strdup("PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin");
	var.path_node = ft_create_env_node(var.path_str);
	add_back_env(&var.env_list, var.path_node);
	var._ = ft_strdup("_=./minishell");
	var._node = ft_create_env_node(var._);
	add_back_env(&var.env_list, var._node);
	return (var.env_list);
}
void	check_env(char **env, t_env **my_env_list)
{
	if (env && env[0])
	{
		*my_env_list = init_env_list(env);
		if (!check_if_there_is_path(env))
		{
			g_general.PATH_NODE = ft_create_env_node(g_general.PATH);
			add_back_env(my_env_list, g_general.PATH_NODE);
		}
		if (!check_if_there_is_pwd(env))
		{
			g_general.PWD_NODE = ft_create_env_node(g_general.PWD);
			add_back_env(my_env_list, g_general.PWD_NODE);
		}
	}
	else
	{
        *my_env_list = generate_minimal_env();
        g_general.env_list = *my_env_list;
	}
}
