#include "./includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_general g_general;

void h(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void add_back_env(t_env **head, t_env *new_node)
{
	t_env *tmp;

	if (!head || !new_node)
		return;

	if (!*head)
	{
		*head = new_node;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int check_if_there_is_path(char **env)
{
	int i;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return 1;
		}
		i++;
	}
	return 0;
}
int check_if_there_is_pwd(char **env)
{
	int i;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			return 1;
		}
		i++;
	}
	return 0;
}
t_env *generate_minimal_env(void)
{
	t_env *env_list = NULL;
	char cwd[1024];
	char *shlvl;
	
	// Get current working directory
	if (getcwd(cwd, sizeof(cwd)))
	{
		char *pwd_str = ft_strjoin("PWD=", cwd);
		t_env *pwd_node = ft_create_env_node(pwd_str);
		add_back_env(&env_list, pwd_node);
	}
	
	// Create SHLVL=1
	shlvl = ft_itoa(1);
	if (shlvl)
	{
		char *shlvl_str = ft_strjoin("SHLVL=", shlvl);
		t_env *shlvl_node = ft_create_env_node(shlvl_str);
		add_back_env(&env_list, shlvl_node);
	}
	
	// Create PATH with default value (not exported in env output)
	char *path_str = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	t_env *path_node = ft_create_env_node(path_str);
	add_back_env(&env_list, path_node);
	
	return env_list;
}
int main(int argc, char **argv, char **env)
{
	t_list *list;
	t_env *my_env_list;
	char *input;
	g_general.PATH = "PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin";
	g_general.PWD="PWD=/home/imiqor/Desktop/minishell";

	(void)argc;
	(void)argv;
	(void)env;
	ft_gc(0,'s');
	if (env && env[0])
	{
		printf("there is env\n");
		my_env_list = init_env_list(env);
		if (!check_if_there_is_path(env))
		{
			printf("a\n");
			g_general.PATH_NODE = ft_create_env_node(g_general.PATH);;
			add_back_env(&my_env_list, g_general.PATH_NODE);
		}
		if(!check_if_there_is_pwd(env))
		{
			printf("b\n");	
			g_general.PWD_NODE = ft_create_env_node(g_general.PWD);
			add_back_env(&my_env_list, g_general.PWD_NODE);
		}
		else if(check_if_there_is_path(env) &&check_if_there_is_pwd(env))
		{
			printf("hiii\n");
			my_env_list = init_env_list(env);
		}
		
	}
	else
	{
		printf("there is no env\n");
		g_general.env_list =my_env_list=generate_minimal_env();
	}
	
	signal(SIGINT, h);
	signal(SIGQUIT, SIG_IGN);
	env_list_to_array(my_env_list);
	while (1)
	{
		input = readline("minishell::::::");
		if (input == NULL)
			break;
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
