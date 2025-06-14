/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:53:05 by imiqor            #+#    #+#             */
/*   Updated: 2025/06/12 22:08:36 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric_argument(const char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (g_general.exit_status);
	while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
		i++;
	while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '\0')
		return (1);
	else
		return (0);
}

int	is_exit_code_overflow(const char *arg)
{
	int					sign;
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	sign = 1;
	while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i++] == '-')
			sign = -1;
	}
	while (arg[i] == '0')
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
	{
		result = result * 10 + (arg[i] - '0');
		if ((sign == 1 && result > 9223372036854775807ULL) || (sign == -1
				&& result > 9223372036854775808ULL))
			return (1);
		i++;
	}
	return (0);
}

void	exit_error_numeric(char *arg)
{
	write(2, "exit: ", 7);
	write(2, arg, ft_strlen(arg));
	write(2, ":numeric argument required\n", 28);
	cleanup_and_exit(2);
}

void	exit_error_too_many_args(void)
{
	write(2, "exit: too many arguments\n", 26);
	g_general.exit_status = 1;
}
void	cleanup_and_exit(int status)
{
	ft_gc(0, 'f');
	ft_gc(0, 'p');
	close(g_general.in);
	close(g_general.out);
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);
	exit(status);
}