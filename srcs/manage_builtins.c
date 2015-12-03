/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:43:03 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:43:04 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		part_one(char **command, t_sh *shell)
{
	if (ft_strcmp(command[0], "env") == 0)
	{
		builtin_env(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		builtin_unsetenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		builtin_exit(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "setenv") == 0)
	{
		builtin_setenv(command, shell);
		return (1);
	}
	return (0);
}

int		part_two(char **command, t_sh *shell)
{
	if (ft_strcmp(command[0], "getenv") == 0)
	{
		builtin_getenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "cd") == 0)
	{
		builtin_cd(command, shell);
		return (1);
	}
	return (0);
}

int		manage_builtins(char **command, t_sh *shell)
{
	if (part_one(command, shell))
		return (1);
	if (part_two(command, shell))
		return (1);
	return (0);
}
