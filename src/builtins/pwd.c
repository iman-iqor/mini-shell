#include"../../includes/minishell.h"


void	pwd(void)
{
	char *cwd ; // will malloc the exact needed space
    cwd = getcwd(NULL, 0);

	if (cwd == NULL)//in the case where the path could be deleted
	{
		printf("%s\n", g_general.old_pwd);
		g_general.exit_status = 1;
		return;
	}
    printf("%s\n", cwd);
    free(cwd);
	g_general.exit_status = 0;
}
