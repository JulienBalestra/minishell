#include "libft.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void ft_remove_endline(char *str)
{
	size_t len;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
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