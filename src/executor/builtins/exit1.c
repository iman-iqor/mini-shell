/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:05 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/12 22:08:47 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_int_overflow(long number, char *str)
{
	if (number > 2147483647 || number < -2147483648)
	{
		exit_error_numeric(str);
	}
}

void	init_vars(t_atoa_state *vars)
{
	vars->i = 0;
	vars->result = 0;
	vars->signe = 1;
}

int	ff_atoi(char *str)
{
	t_atoa_state	vars;

	init_vars(&vars);
	while (str[vars.i] == '\t' || str[vars.i] == '\n' || str[vars.i] == '\v'
		|| str[vars.i] == '\f' || str[vars.i] == '\r' || str[vars.i] == ' ')
		vars.i++;
	if (str[vars.i] == '-' || str[vars.i] == '+')
	{
		if (str[vars.i] == '-')
			vars.signe = -1;
		vars.i++;
	}
	while (str[vars.i] >= '0' && str[vars.i] <= '9')
	{
		vars.result = vars.result * 10 + str[vars.i] - 48;
		check_int_overflow(vars.result * vars.signe, str);
		vars.i++;
	}
	return ((int)(vars.result * vars.signe));
}

void	ft_exit(char **args)
{
	int	exit_code;

	write(2, "exit\n", 5);
	if (!args || !args[0])
	{
		cleanup_and_exit(g_general.exit_status);
	}
	if (!is_numeric_argument(args[0]))
		exit_error_numeric(args[0]);
	if (args[1])
	{
		write(2, "exit: too many arguments\n", 26);
		g_general.exit_status = 1;
		return ;
	}
	if (args[0] && args)
	{
		exit_code = ff_atoi(args[0]);
		cleanup_and_exit(exit_code);
	}
}
