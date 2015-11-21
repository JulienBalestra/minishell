#include <stdlib.h>
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void ft_remove_endline(char *str)
{
	size_t len;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
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

int existing_line(t_sh *shell)
{
	if (shell->buf == NULL)
	{
		shell->exit = 1;
		return (0);
	}
	else if (is_only_spaces(shell->buf))
	{
		free(shell->buf);
		shell->buf = NULL;
		return (0);
	}
	return (1);
}

char **build_command(t_sh *shell)
{
	char **command;
	char *no_spaces;

	ft_remove_endline(shell->buf);
	convert_chars(shell->buf);
	no_spaces = ft_remove_useless(shell->buf, ' ');
	command = ft_lz_strsplit(no_spaces, ' ');
	ft_strdel(&no_spaces);
	manage_interpretor(command, shell);
	free(shell->buf);
	shell->buf = NULL;
	return (command);
}