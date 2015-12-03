/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:32 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:33 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		have_null(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (i == 1 && is_null_arg(command[i]))
			return (1);
		else if (is_setenv(command[i]))
			return (0);
		else if (ft_strcmp("-u", command[i - 1]) != 0 &&
				is_null_arg(command[i]))
			return (1);
		i++;
	}
	return (0);
}

int		have_ignore(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (i == 1 && is_ignore_arg(command[i]))
			return (1);
		else if (is_setenv(command[i]))
			return (0);
		else if (ft_strcmp("-u", command[i - 1]) != 0 &&
				is_ignore_arg(command[i]))
			return (1);
		i++;
	}
	return (0);
}

int		have_setenv(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (i == 1 && is_setenv(command[i]))
			return (1);
		else if (ft_strcmp("-u", command[i - 1]) != 0 && is_setenv(command[i]))
			return (1);
		i++;
	}
	return (0);
}

int		have_unsets(char **command)
{
	int i;
	int u;

	i = 1;
	u = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "-u") == 0 && command[i + 1])
		{
			i = i + 2;
			u = 1;
		}
		else if (ft_strcmp(command[i], "-u") == 0)
			return (-1);
		else if (is_setenv(command[i]))
			return (u);
		else if (is_ignore_arg(command[i]) || is_null_arg(command[i]))
			i++;
		else
			break ;
	}
	return (u);
}

int		have_command(char **command)
{
	int	i;
	int	set;

	i = 1;
	set = 0;
	while (command[i])
	{
		if (set == 0 && ft_strcmp(command[i], "-u") == 0 && command[i + 1])
		{
			i = i + 2;
		}
		else if (set == 0 && (is_ignore_arg(command[i]) ||
				is_null_arg(command[i])))
			i++;
		else if (is_setenv(command[i]))
		{
			i++;
			set = 1;
		}
		else
			return (1);
	}
	return (0);
}
