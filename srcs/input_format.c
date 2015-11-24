#include <stdlib.h>
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char ***command_from_cli(char **cli, t_sh *shell)
{
	int i;
	char ***cmd;
	char *no_space;

	i = 0;
	if ((cmd = (char ***)malloc(sizeof(char **) * (ft_str2len(cli) + 1) )))
	{
		while (cli[i])
		{
			no_space = ft_remove_useless(cli[i], ' ');
			cmd[i] = ft_lz_strsplit(no_space, ' ');
			ft_strdel(&no_space);
			manage_interpretor(cmd[i], shell);
			i++;
		}
		cmd[i] = NULL;
	}
	return (cmd);
}

char ***build_command(t_sh *shell)
{
	char ***command;
	char **multi_cli;
	//char *spaces;
	//char *semi;

	/*ft_remove_endchar(shell->buf);
	convert_chars(shell->buf);
	spaces = ft_remove_useless(shell->buf, ' ');
	semi = ft_remove_useless(spaces, ';');
	ft_strdel(&spaces);
	cli = ft_lz_strsplit(semi, ';');*/

	multi_cli = ft_lz_strsplit(shell->buf, ';');
	//ft_strdel(&semi);
	command = command_from_cli(multi_cli, shell);
	ft_str2del(multi_cli);
	free(shell->buf);
	shell->buf = NULL;
	return (command);
}