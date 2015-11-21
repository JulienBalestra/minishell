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

int is_only_endline(char *buf)
{
	if (buf[0] && buf[1] && buf[0] == '\n' && buf[1] == '\0')
		return (1);
	else
		return (0);
}

int is_only_one_line(char *buf)
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
		if (i == len - 1)
			return (1);
	}
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

char **build_command(char *buf, t_sh *shell)
{
	char **command;
	char *no_spaces;

	ft_remove_endline(buf);
	convert_chars(buf);
	no_spaces = ft_remove_useless(buf, ' ');
	command = ft_lz_strsplit(no_spaces, ' ');
	ft_strdel(&no_spaces);
	manage_interpretor(command, shell);
	return (command);

}