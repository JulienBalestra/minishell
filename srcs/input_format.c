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
