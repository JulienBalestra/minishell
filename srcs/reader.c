#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int is_enter(char *buf)
{
	if (buf && ft_strlen(buf) == 1 && buf[0] == '\n')
		return (1);
	return (0);
}

char *get_line(t_sh *shell)
{
	char *buf;
	ssize_t ret;

	if ((buf = (char *)malloc(sizeof(char) * BUFF_SIZE)))
	{
		buf_init(buf, BUFF_SIZE);
		while ((ret = read(0, buf, BUFF_SIZE)))
		{
			if (is_real_line(buf))
			{
				return (buf);
			}
            else if (is_enter(buf))
			{
				display_prompt(shell);
				ft_strclr(buf);
			}
		}
		free(buf);
		shell->exit = 1;
	}
	return (NULL);
}