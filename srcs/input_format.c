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

char ***command_from_cli(char **cli, t_sh *shell)
{
	int i;
	size_t len;
	char ***command;
	char *no_spaces;

	i = 0;
	len = ft_str2len(cli);
	if ((command = (char ***)malloc(sizeof(char **) * (len + 1) )))
	{
		while (cli[i])
		{
			no_spaces = ft_remove_useless(cli[i], ' ');
			command[i] = ft_lz_strsplit(no_spaces, ' ');
			ft_strdel(&no_spaces);
			ft_strdel(&cli[i]);
			manage_interpretor(command[i], shell);
			i++;
		}
		free(cli);
		command[i] = NULL;
	}
	return (command);
}

char ***build_command(t_sh *shell)
{
	char ***command;
	char **cli;
	char *spaces;
	char *semi;

	ft_remove_endline(shell->buf);
	convert_chars(shell->buf);
	spaces = ft_remove_useless(shell->buf, ' ');
	semi = ft_remove_useless(spaces, ';');
	ft_strdel(&spaces);
	cli = ft_lz_strsplit(semi, ';');
	ft_strdel(&semi);
	command = command_from_cli(cli, shell);
	free(shell->buf);
	shell->buf = NULL;
	return (command);
}