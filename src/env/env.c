// #include"../../includes/minishell.h"


// // vars exists
// t_envp	*envar_in(t_envp *env, char *key)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, key) == 0)
// 		{
// 			return (env);
// 		}
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// // get var
// t_envp	*get_envar(char *key)
// {
// 	t_envp	*node;

// 	node = g_global_var.env;
// 	while (node)
// 	{
// 		if (node->exists && ft_strcmp(node->key, key) == 0)
// 		{
// 			return (node);
// 		}
// 		node = node->next;
// 	}
// 	return (NULL);
// }


// // number of vars
// int	env_len(void)
// {
// 	t_envp	*list;
// 	int		i;

// 	list = g_global_var.env;
// 	i = 0;
// 	while (list)
// 	{
// 		i++;
// 		list = list->next;
// 	}
// 	return (i);
// }
// // env to string key ,  value => "key=value"
// char	*kv_to_str(t_envp *env)
// {
// 	char	*result;
// 	char	*i;

// 	result = ft_strjoin(env->key, "=");
// 	if (result == NULL)
// 		return (NULL);
// 	i = result;
// 	if (env->value == NULL)
// 		result = ft_strjoin(i, "");
// 	else
// 		result = ft_strjoin(i, env->value);
// 	return (result);
// }
// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str1;
// 	char	*str2;
// 	char	*ptr;
// 	char	*start;
// 	size_t	len;

// 	str1 = (char *)s1;
// 	str2 = (char *)s2;
// 	len = ft_strlen(str1) + ft_strlen(str2);
// 	if (!str1 || !str2)
// 		return (NULL);
// 	ptr = (char *)gc_alloc(sizeof(char) * (len + 1));
// 	if (!ptr)
// 		return (NULL);
// 	start = ptr;
// 	while (*str1)
// 		*start++ = *str1++;
// 	while (*str2)
// 		*start++ = *str2++;
// 	*start = '\0';
// 	return (ptr);
// }


// //return the variables of two d pointer
// char	**get_env(void)
// {
// 	char	**list;
// 	t_envp	*env;
// 	int		i;

// 	env = g_global_var.env;
// 	i = 0;
// 	list = gc_alloc((env_len() + 1) * sizeof(char *));
// 	if (list == NULL)
// 		return (NULL);
// 	while (env)
// 	{
// 		if (env->exists)
// 		{
// 			list[i] = kv_to_str(env);
// 			if (list[i++] == NULL)
// 			{
// 				return (NULL);
// 			}
// 		}
// 		env = env->next;
// 	}
// 	list[i] = NULL;
// 	return (list);
// }
