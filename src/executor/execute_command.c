#include "../includes/minishell.h"

int    ft_execve(char *exact_path, t_list *list)
{
    env_list_to_array(g_general.env_list);
    execve(exact_path, list->argument, g_general.env_array);
   if (errno == EACCES)
	{
		write(2, "minishell: permission denied: ", 30);
		write(2, exact_path, strlen(exact_path));
		write(2, "\n", 1);
		imane_exit(126);
	}
	else if (errno == ENOENT)
	{
		write(2, "minishell: ", 12);
		write(2, exact_path, strlen(exact_path));
		write(2, " :No such file or directory", 28);
		write(2, "\n", 1);
		imane_exit(127);
	}
	else
	{
		perror("minishell"); // for other errors
		imane_exit(127);
	}
    return (0);
}

char    **extract_path(char **env)
{
    int    i;

    i = 0;
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

char    *concatenate_path(char *dir, char *cmd)
{
    char    *tmp;
    char    *full_path;

    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return (NULL);
    full_path = ft_strjoin(tmp, cmd);
    return (full_path);
}

char    *check_path(char **env, t_list *list)
{
    char    **paths;
    char    *path;
    int        i;
    
    i = 0;
    if (ft_strchr(list->argument[0], '/'))
        return (ft_strdup(list->argument[0]));
    paths = extract_path(env);
    if (!paths)
    {
        write(2, "minishell: PATH not set\n", 25);
        imane_exit(127);
    }
    while (paths[i])
    {
        path = concatenate_path(paths[i], list->argument[0]);
        if (access(path, F_OK) == 0)
        {
            return (path);
        }
        i++;
    }
    return (NULL);
}
int	handle_directory_or_path_errors(t_list *list)
{
	if (open(list->argument[0], __O_DIRECTORY) != -1)
	{
		write(2, list->argument[0], ft_strlen(list->argument[0]));
		write(2, ": is a directory\n", 17);
		imane_exit(126);
	}
	if (!get_envar("PATH"))
	{
		write(2, list->argument[0], ft_strlen(list->argument[0]));
		write(2, " : No such file or directory\n", 30);
		imane_exit(127);
	}
	return (0);
}


int	execute_command(t_list *list)
{
	char	*exact_path;

	if (!list || !list->argument || !list->argument[0])
		imane_exit(127);
	if (ft_strlen(list->argument[0]) == 0)
	{
		g_general.exit_status = 0;
		return (1);
	}
	if (handle_directory_or_path_errors(list))
		return (1);
	if (is_builtin(list->argument[0]))
	{
		exec_builtin(list);
		imane_exit(g_general.exit_status);
	}
	env_list_to_array(g_general.env_list);
	exact_path = check_path(g_general.env_array, list);
	if (!exact_path)
	{
		write(2, list->argument[0], ft_strlen(list->argument[0]));
		write(2, ": command not found\n", 21);
		imane_exit(127);
	}
	ft_execve(exact_path, list);
	return (0);
}

