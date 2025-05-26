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
int if_else_of_cd(char **path, t_env *home, char **p)
{
	if (path && path[0] && path[1])
		return cd_error(0), 1;
	if ((!path || !path[0]) && home)
		*p = home->value;
	else if (path)
		*p = *path;

	if (*p && chdir(*p))
		return cd_error(2), 1;

	if (!*p)
		return cd_error(1), 1;

	return 0;
}
void update_pwd()
{
	char* current_directory;
	current_directory =  getcwd(NULL,0);
	t_env *pwd;
	pwd=get_envar("PWD");
	if(!pwd)
	printf("====\n");
	pwd->value=ft_gc(ft_strlen(current_directory) + 1,'m');
	ft_strcpy(pwd->value, current_directory);
}
void	cd(char **path)
{
	char	*p;
	t_env	*home;

	home = get_envar("HOME");
	p = NULL;
	if (if_else_of_cd(path, home, &p))
		return;
	update_pwd();
	g_general.exit_status = 0;
}

