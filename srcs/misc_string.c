#include <stdlib.h>
#include "../libft/includes/libft.h"

void str_clear(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = '\0';
        i++;
    }
}

void buf_init(char *buf, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        buf[i] = '\0';
        i++;
    }
}

char *triple_join(char *s1, char *s2, char *s3)
{
    char *final;
    size_t total_len;
    int i;

    total_len = ft_strlen(s1)+ ft_strlen(s2) + ft_strlen(s3) + 1;
    i = 0;
    if ((final = (char *)malloc(sizeof(char) * total_len )))
    {
        while (*s1)
        {
            final[i++] = *s1;
            s1++;
        }
        while (*s2)
        {
            final[i++] = *s2;
            s2++;
        }
        while (*s3)
        {
            final[i++] = *s3;
            s3++;
        }
        final[i] = '\0';
    }
    return (final);
}