#include"../../includes/minishell.h"
static void	cd_1(int code)
{
	if (code == 1)
		write(2, "cd: HOME not set\n", 18);
	else if (code == 0)
		write(2, "cd :too many arguments\n", 23);
	else if (code == 2)
		perror("cd");
	g_general.exit_status = 1;
    
}

void	cd(char **path)
{
	char	*p;
	t_env	*home;

	home = get_envar("HOME");
	p = NULL;
	if (path && *path && *(path + 1))
	{
		cd_1(0);
		return ;
	}
	if (path && path[0] == NULL && home)
		p = home->value;
	else if (path)
		p = *path;
	if (p && chdir(p))
	{
		cd_1(2);
		return ;
	}
	else if (!p)
	{
		cd_1(1);
		return ;
	}
	g_general.exit_status = 0;
}

