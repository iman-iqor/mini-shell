#include "../../includes/minishell.h"


void export_logique(char **list)
{
    t_env *node;
    char *key, *value;

    if (!get_key_and_value(list[0], &key, &value))
        return ;

    node = get_envar_with_passing_env_list(g_general.env_list, key);
    if (node)
    {
        if (value)
            node->value = value;
    }
    else
    {
        node = add_env_var(key, value, last_envar(g_general.env_list));
        if (node)
            addback(node);
    }
}

void print_env_var(t_env *env)
{
    write(1, "declare -x ", 11);
    write(1, env->key, ft_strlen(env->key));
    if (env->value)
    {
        write(1, "=\"", 2);
        write(1, env->value, ft_strlen(env->value));
        write(1, "\"", 1);
    }
    write(1, "\n", 1);
}

void sort_ascii(char **arr)
{
    int i = 0;
    char *tmp;
    while (arr && arr[i])
    {
        int j = 0;
        while (arr[j + 1])
        {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void print_export_sorted(char **keys, t_env *env_list)
{
    int i = 0;
    t_env *var;

    while (keys && keys[i])
    {
        var = get_envar_with_passing_env_list(env_list, keys[i]);
        print_env_var(var);
        i++;
    }
}

void export_no_args(void)
{
    char **keys = get_env_keys(g_general.env_list);
    sort_ascii(keys);
    print_export_sorted(keys, g_general.env_list);
}