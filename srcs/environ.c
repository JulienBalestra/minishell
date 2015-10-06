#include <stdlib.h>
#include "libft.h"

char **environ(void)
{
    char *str_path;
    char **path;

    str_path = NULL;
    path = NULL;
    if ((str_path = getenv("PATH")))
    {
        path = ft_lz_strsplit(str_path, ':');
        ft_strdel(&str_path);
    }
    return (str_path);
}