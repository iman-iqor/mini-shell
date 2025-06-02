#include"../../includes/minishell.h"


void	pwd(void)
{
	char *cwd ; // will malloc the exact needed space
    cwd = getcwd(NULL, 0);

	if (cwd == NULL)//in the case where the path could be deleted
	{
		if(g_general.old_pwd)
			printf("%s\n", g_general.old_pwd);
		g_general.exit_status = 0;
		return;
	}
    printf("%s\n", cwd);
    free(cwd);
	// free(g_general.old_pwd);
	g_general.exit_status = 0;
}
