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

// t_env generate_env_list()
// {
// 	t_env	*head;
// 	t_env	*node;
// 	t_env	*last;
// 	int		i;
// 	char env[]={"PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin","OLD_PWD="};

// 	head = NULL;
// 	last = NULL;
// 	i = 0;
// 	while (env[i])
// 	{
// 		node = ft_create_env_node(env[i]);

// 		if (last == NULL)
// 			head = node;
// 		else
// 			last->next = node;
// 		last = node;
// 		i++;
// 	}
// 	g_general.env_list = head;
// 	return (head);
// }

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
int main(int argc, char **argv, char **env)
{
	t_list *list;
	t_env *my_env_list;
	char *input;
	g_general.PATH = "PATH=/app/bin:/app/bin:/app/bin:/usr/bin:/home/imiqor/.var/app/com.visualstudio.code/data/node_modules/bin";

	(void)argc;
	(void)argv;
	(void)env;

	if (env)
	{
		if (!check_if_there_is_path(env))
		{
			my_env_list = init_env_list(env);
			g_general.PATH_NODE = ft_create_env_node(g_general.PATH);
			
			add_back_env(&my_env_list, g_general.PATH_NODE);
		}
		else
		{
			printf("f\n");
			my_env_list = init_env_list(env);
		}
	}
	// else
	// 	my_env_list=generate_my_env_list();

	// my_env_list = init_env_list(env);
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
