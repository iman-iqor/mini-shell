/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:59 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/12 22:28:03 by imiqor           ###   ########.fr       */
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
		// i need here to free the memory and exit with 130 not just exit
	}
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
