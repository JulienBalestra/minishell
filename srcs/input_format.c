/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:45 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:47 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char	***command_from_cli(char **cli)
{
	int		i;
	char	***cmd;
	char	*no_space;

	i = 0;
	if ((cmd = (char ***)malloc(sizeof(char **) * (ft_str2len(cli) + 1))))
	{
		while (cli[i])
		{
			no_space = ft_remove_useless(cli[i], ' ');
			cmd[i] = ft_lz_strsplit(no_space, ' ');
			ft_strdel(&no_space);
			i++;
		}
		cmd[i] = NULL;
	}
	return (cmd);
}

char	***build_command(t_sh *shell)
{
	char	***command;
	char	**multi_cli;

	command = NULL;
	if ((multi_cli = ft_lz_strsplit(shell->buf, ';')))
	{
		command = command_from_cli(multi_cli);
		ft_str2del(multi_cli);
		free(shell->buf);
		shell->buf = NULL;
	}
	return (command);
}
