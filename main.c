/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:05:22 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/25 21:34:34 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_general	g_general;

void	handle_input_loop(void)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		input = readline("minishell::::");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		if (is_only_spaces(input) == 0)
		{
			free(input);
			continue ;
		}
		list = parse_cmd(input);
		if (list)
			ft_exec(list);
		free(input);
	}
}

void	aghlimi(void)
{
	printf("[H[2J[3J\033[95m██╗███╗   ███╗██╗ ██████╗  ██████╗ ██████╗ "
		"        ██████╗ ███████╗███╗   ██╗   "
		"  ██╗██████╗  █████╗ ██████╗  █████╗ \n"
		"██║████╗ ████║██║██╔═══██╗██╔═══██╗██╔══██╗        "
		"██╔══██╗██╔════╝████╗  ██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n"
		"██║██╔████╔██║██║██║   ██║██║   ██║██████╔╝        "
		"██████╔╝█████╗  ██╔██╗ ██║    "
		" ██║██████╔╝███████║██████╔╝███████║\n"
		"██║██║╚██╔╝██║██║██║▄▄ ██║██║   ██║██╔══██╗        ██╔══██╗██╔══╝ "
		" ██║╚██╗██║██   ██║██╔══██╗██╔══██║██╔══██╗██╔══██║\n"
		"██║██║ ╚═╝ ██║██║╚██████╔╝╚██████╔╝██║  ██║███████╗██████╔╝███████╗██║"
		" ╚████║╚█████╔╝██████╔╝██║  ██║██║  ██║██║  ██║\n"
		"╚═╝╚═╝     ╚═╝╚═╝ ╚══▀▀═╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═════╝ ╚══════╝╚═╝"
		"  ╚═══╝ ╚════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝\033[0m\n");
}

int	main(int argc, char **argv, char **env)
{
	t_env	*my_env_list;

	aghlimi();
	check_args(argc, argv);
	setup_env(env, &my_env_list);
	signal(SIGINT, h);
	signal(SIGQUIT, SIG_IGN);
	handle_input_loop();
	clear_history();
	graceful_exit();
	return (0);
}
