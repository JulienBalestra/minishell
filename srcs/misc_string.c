#include <stdlib.h>
#include "libft.h"

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

	total_len = ft_nstrlen(s1) + ft_nstrlen(s2) + ft_nstrlen(s3) + 1;
	i = 0;
	if ((final = (char *) malloc(sizeof(char) * total_len)))
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
		while (s3 && *s3)
		{
			final[i++] = *s3;
			s3++;
		}
		final[i] = '\0';
	}
	return (final);
}

void convert_chars(char *str)
{
	while (*str)
	{
		if (*str == '\t' || *str == '\b' || *str == '\n' || *str == '\r' || *str == '\f')
			*str = ' ';
		str++;
	}
}