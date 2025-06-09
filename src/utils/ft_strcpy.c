#include "../../includes/minishell.h"


char *ft_strcpy(char *dest, char *src)
{
    int i;
    i = 0;
    if (!dest || !src)
        return (ft_strdup(" "));
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
