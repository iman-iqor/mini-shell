
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


 void	exit_error_numeric(char *arg)
{
	write(2, "exit: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 29);
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
	(void)status;
	exit(status);
}
int	is_empty_or_null(char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s != ' ' && (*s < 9 || *s > 13)) // not whitespace
			return (0);
		s++;
	}
	return (1);
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
		write(2, "exit: too many arguments imane\n", 32);
		g_general.exit_status = 1;
		return ;
	}
	if(args[0]&& args)
	{
		printf("there is args[0]\n");
		exit_code = ft_atoi(args[0]);
		cleanup_and_exit(exit_code);
	}
	
}

