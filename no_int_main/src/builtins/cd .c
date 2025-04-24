#include"../../includes/minishell.h"
void	cd_error(int code)
{
	if (code == 1)
		write(2, "cd: HOME not set\n", 18);
	else if (code == 0)
		write(2, "cd :too many arguments\n", 23);
	else if (code == 2)
		perror("cd");
	g_general.exit_status = 1;
    
}


//i need to see if the path exist by comparing the key i reicived and the node->vkey in the node
t_env	*get_envar(char *key)
{
	t_env	*node;

	node = g_general.env_list;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}
void	cd(char **path)
{
	char	*p;
	t_env	*home;

	home = get_envar("HOME");
	p = NULL;
	if (path && *path && *(path + 1))
	{
		cd_error(0);
		return ;
	}
	if (path && path[0] == NULL && home)
		p = home->value;
	else if (path)
		p = *path;
	if (p && chdir(p))
	{
		cd_error(2);
		return ;
	}
	else if (!p)
	{
		cd_error(1);
		return ;
	}
	g_general.exit_status = 0;
}

