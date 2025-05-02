
#include "../../includes/minishell.h"


char **get_env_keys(t_env *env_list)
{
    int size = 0;
    t_env *tmp = env_list;
    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }

    char **keys = ft_gc(sizeof(char *) * (size + 1),'m');  // +1 for the NULL terminator
    if (!keys)
        return (NULL);

    tmp = env_list;
    for (int i = 0; tmp; i++)
    {
        keys[i] = ft_strdup(tmp->key);
        tmp = tmp->next;
    }
    keys[size] = NULL;  // NULL-terminated
    return keys;
}

int is_valid(char *str)
{
    int i = 0;

    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;

    if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
        return (0);

    while (str[i] && str[i] != '=')
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}
void handle_exit_status(int flag)
{
	if(flag)
		g_general.exit_status = 2;
	else	
		g_general.exit_status = 0;
}
void export(char **list)
{
    if (list && list[0])  // Check if there are any arguments
    {
		int i;
		int flag;
		flag  = 0;
		i = 0;
        while(list[i] != NULL)  // Loop through all variables
        {
            if (!is_valid(list[i]))  // Validate each argument
            {
                write(2,"export: not a valid identifier\n", 32);
				flag = 1;
            }
			else
            	export_logique(&list[i]);  // Process each variable
			i++;
        }
		handle_exit_status(flag);
    }
    else
    {
        export_no_args();  // If no arguments, show the list of exported variables
        g_general.exit_status = 0;
    }
}
