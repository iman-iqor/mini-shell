#include "../../includes/minishell.h"


t_env *last_envar(t_env *env_list)
{
    t_env *tmp = env_list;
    while (tmp && tmp->next)
    {
        tmp = tmp->next;
    }
    return tmp;
}

void addback(t_env *new_node)
{
    t_env *tmp = g_general.env_list;
    if (!tmp)
    {
        g_general.env_list = new_node;
    }
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}
t_env *get_envar_with_passing_env_list(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

int get_key_and_value(char *str, char **key, char **value)
{
    char *equal_sign = ft_strchr(str, '=');
    if (equal_sign)
    {
        *key = ft_substr(str, 0, equal_sign - str);  // Simplify using ft_substr
        *value = ft_strdup(equal_sign + 1);
    }
    else
    {
        *key = ft_strdup(str);
        *value = NULL;
    }
    return (*key != NULL);
}

t_env *add_env_var(char *key, char *value, t_env *prev)
{
    t_env *env = ft_gc(sizeof(t_env),'m');
    if (env)
    {
        env->key = key;
        env->value = value;
        env->prev = prev;
        env->next = NULL;
    }
    return env;
}