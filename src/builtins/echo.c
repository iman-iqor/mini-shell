#include"../../includes/minishell.h"
int	is_flag(char *str)
{
	int	i;

	if (str)
	{
		if (ft_strcmp(str, "-n") == 0)
		{
			return (0);
		}
		if (str[0] == '-')
		{
			i = 1;
			while (str[i] == 'n')
				i++;
			if (str[i] == 0)
			{
				return (0);
			}
		}
	}
	return (1);
}

void	echo(char **list)
{

	
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (list && list[i] && is_flag(list[i]) == 0)
	{
		flag = 1;
		i++;
	}
	while (list && list[i])
	{
		write(1, list[i], ft_strlen(list[i]));
		if (list[++i])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	g_general.exit_status = 0;

}