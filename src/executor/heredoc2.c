/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:59 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/26 15:51:49 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_general.exit_status = 130;
		imane_exit(130);
	}
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	hh(int status)
{
	if (status == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		write(1, "\n", 1);
	}
}

void	hhh(int status)
{
	if (status == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		write(1, "Quit (core dumped)\n", 20);
	}
}
