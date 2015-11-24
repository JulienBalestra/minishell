#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char *compile(char *left, char *buf)
{
	char *tmp;

	tmp = buf;
	buf = ft_strjoin(left, buf);
	free(tmp);
	ft_strdel(&left);
	return (buf);
}

void again(char *buf, t_sh *shell)
{
	display_prompt(shell);
	ft_strclr(buf);
}

char *move_and_clean(char *buf)
{
	char *left;

	left = ft_strdup(buf);
	ft_strclr(buf);
	return (left);
}

char *get_line(t_sh *shell)
{
	char *buf;
	char *left;
	ssize_t ret;

	if ((buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
	{
		left = NULL;
		display_prompt(shell);
		buf_init(buf, BUFF_SIZE);
		while ((ret = read(0, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			if (left && buf[0])
				buf = compile(left, buf);
			if (is_real_line(buf))
				return (buf);
            else if (is_enter(buf))
				again(buf, shell);
			else
				left = move_and_clean(buf);
		}
		if (left)
			free(left);
		free(buf);
		shell->exit = 1;
	}
	return (NULL);
}