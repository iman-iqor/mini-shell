/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:05:22 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/27 15:41:11 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	update_shlvl(t_env **env)
{
	t_env	*tmp;
	int		new_level;

	tmp = *env;
	while (tmp && ft_strcmp(tmp->key, "SHLVL"))
		tmp = tmp->next;
	if (tmp)
	{
		new_level = ft_atoi(tmp->value) + 1;
		if (new_level < 0)
			new_level = 0;
		if (new_level > 999)
		{
			printf("%s%d%s", "minishell: warning: shell level(", new_level,
				") too high, resetting to 1\n");
			new_level = 1;
		}
		tmp->value = ft_itoa(new_level);
	}
	else
		add_back_env(env, ft_create_env_node("SHLVL=1"));
}

int	is_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 32)
			return (1);
		i++;
	}
	return (0);
}

void	h(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		exit(printf("Error: try only 1 argument"));
	return (0);
}

void	setup_env(char **env, t_env **my_env_list)
{
	char	*p;

	p = getcwd(NULL, 0);
	g_general.pwdd = ft_strjoin("PWD=", p);
	free(p);
	ft_gc(0, 's');
	check_env(env, my_env_list);
	update_shlvl(my_env_list);
	g_general.env_list = *my_env_list;
	g_general.env_array = env_list_to_array(*my_env_list);
}

