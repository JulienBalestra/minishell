#include "libft.h"
#include <stdlib.h>

char *ft_remove_endline(char *str)
{
    char *new_str;
    int len;
    int i;

    new_str = NULL;
    len = ft_strlen(str);
    i = 0;
    if (str[len -1] == '\n')
    {
        if ((new_str = (char *)malloc(sizeof(char) * len)))
        {
            while (i < len -1)
            {
                new_str[i] = str[i];
                i++;
            }
            new_str[i] = '\0';
        }
        return (new_str);
    }
    else
    {
        return (str);
    }
}

int is_only_endline(char *buf)
{
    if (buf[0] && buf[1] && buf[0] == '\n' && buf[1] == '\0')
        return (1);
    else
        return (0);
}

int is_only_spaces(char *buf)
{
    size_t i;

    i = 0;
    while (i < ft_strlen(buf) - 1)
    {
        if (ft_isblank(buf[i]))
            i++;
        else
            return (0);
    }
    return (1);
}