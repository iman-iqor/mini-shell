#include "../includes/minishell.h"

int ft_execve(char *exact_path, t_list *list)
{
	env_list_to_array(g_general.env_list);
	execve(exact_path, list->argument, g_general.env_array);

	// If execve fails
	if (access(exact_path, F_OK) == 0 && access(exact_path, X_OK) == -1)
	{
		write(2, "minishell: permission denied: ", 30);
		write(2, exact_path, strlen(exact_path));
		write(2, "\n", 1);
		exit(126);
	}
	else if (access(exact_path, F_OK) != 0)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, exact_path, strlen(exact_path));
		write(2, "\n", 1);
		exit(127);
	}
	perror("minishell");
	exit(127);
}

char **extract_path(char **env)
{
	int i = 0;

	if (!env)
		return (NULL);

	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char *concatenate_path(char *dir, char *cmd)
{
	char *tmp = ft_strjoin(dir, "/");
	char *full_path;

	if (!tmp)
		return (NULL);

	full_path = ft_strjoin(tmp, cmd);
	return (full_path);
}

char *check_path(char **env, t_list *list)
{
	char **paths;
	char *path;
	int i = 0;

	if (ft_strchr(list->argument[0], '/'))
		return (ft_strdup(list->argument[0]));

	paths = extract_path(env);
	if (!paths)
	{
		write(2, "minishell: PATH not set\n", 25);
		exit(127);
	}
	// if (!paths)
	// 	return (NULL); // DON'T exit, just return NULL

	while (paths[i])
	{
		path = concatenate_path(paths[i], list->argument[0]);
		if (access(path, F_OK) == 0)
		{
			return (path);
		}
		i++;
	}
	return (ft_strdup(list->argument[0]));
}

int execute_command(t_list *list)
{
	char *exact_path;
	
	if (list && list->argument && ft_strlen(list->argument[0]) == 0)
	{
		write(2, "minishell: empty command\n", 26);
		exit(127);
	}
	if (open(list->argument[0], __O_DIRECTORY) != -1)
	{

		write(2, list->argument[0], strlen(list->argument[0]));
		write(2, ": is a directory\n", 17);
		exit(126);
	}
	if (is_builtin(list->argument[0]))
	{
		exec_builtin(list);
		exit(g_general.exit_status); // Important to exit after builtin
	}
	else
	{
		exact_path = check_path(g_general.env_array, list);
		ft_execve(exact_path, list);
	}

	// free(exact_path); // Not reached, just in case
	return (0);
}
