
#include "../../includes/minishell.h"

 int	is_numeric_argument(const char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return g_general.exit_status;
	
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
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] == '0')
		i++;

	while (arg[i] && ft_isdigit(arg[i]))
	{
		result = result * 10 + (arg[i] - '0');
		if ((sign == 1 && result > 9223372036854775807ULL) ||
			(sign == -1 && result > 9223372036854775808ULL))
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
	ft_gc(0,'p');
	close(g_general.in);
	close(g_general.out);
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);
	exit(status);
}



/************************* */


typedef struct s_atoa_state
{
	int					i;
	long				result;
	int					signe;
}						t_atoa_state;


void	check_int_overflow(long number,char* str)
{
	if (number > 2147483647  || number < -2147483648 )
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

int	ff_atoi(char* str)
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
		check_int_overflow(vars.result * vars.signe,str);
		vars.i++;
	}
	return ((int)(vars.result * vars.signe));
}






void	ft_exit(char **args)
{
	int	exit_code;

	write(2, "exit\n", 5);
	
	if(!args || !args[0])
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
	if(args[0]&& args)
	{
		exit_code = ff_atoi(args[0]);
		cleanup_and_exit(exit_code);
	}
	
}

