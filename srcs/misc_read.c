#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int is_real_line(char *buf)
{
	size_t len;
	size_t i;

	i = 0;
	if ((len = null_strlen(buf)))
	{
		while (buf[i] && buf[i] != '\n')
		{
			i++;
		}
		if (i == len - 1 && (buf[0] != '\n'))
			return (1);
	}
	return (0);
}