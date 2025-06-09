#include "./includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_general	g_general;

void	h(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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
typedef struct  s_generate_minimal_env
{
	t_env	*env_list;
	char	cwd[1024];
	char	*shlvl;
	char	*pwd_str;
	t_env	*pwd_node;
	char	*shlvl_str;
	t_env	*shlvl_node;
	char	*path_str;
	t_env	*path_node;
} t_generate_minimal_env;

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
			;
			add_back_env(my_env_list, g_general.PATH_NODE);
		}
		if (!check_if_there_is_pwd(env))
		{
			g_general.PWD_NODE = ft_create_env_node(g_general.PWD);
			add_back_env(my_env_list, g_general.PWD_NODE);
		}
		else if (check_if_there_is_path(env) && check_if_there_is_pwd(env))
		{
			*my_env_list = init_env_list(env);
		}
	}
	else
	{
		printf("there is no env a bro\n");
        *my_env_list = generate_minimal_env();
        g_general.env_list = *my_env_list;
	}
}
int	main(int argc, char **argv, char **env)
{
	t_list	*list;
	t_env	*my_env_list;
	char	*input;

	g_general.PATH = "PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin";
	g_general.PWD = "PWD=/home/imiqor/Desktop/minishell";
	(void)argc;
	(void)argv;
	ft_gc(0, 's');
	check_env(env, &my_env_list);
	signal(SIGINT, h);
	signal(SIGQUIT, SIG_IGN);
	env_list_to_array(my_env_list);
	while (1)
	{
		input = readline("minishell::::::");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		list = parse_cmd(input, my_env_list);
		ft_exec(list);
		printf("%d\n", g_general.exit_status);
		free(input);
	}
	graceful_exit();
	return (0);
}
