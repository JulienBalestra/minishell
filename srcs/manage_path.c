/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:43:43 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:43:44 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

int		len_to_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*join_path_to_command(char *command, char *path_value)
{
	int		cur_path_len;
	char	*tmp_cur_path;
	char	*cur_full_cmd;

	cur_path_len = -1;
	while (cur_path_len != 0 && path_value)
	{
		cur_path_len = len_to_char(path_value, ':');
		tmp_cur_path = ft_strndup(path_value, (size_t)cur_path_len);
		cur_full_cmd = triple_join(tmp_cur_path, "/", command);
		free(tmp_cur_path);
		if (access(cur_full_cmd, F_OK) == 0)
			return (cur_full_cmd);
		free(cur_full_cmd);
		if (path_value[cur_path_len] != '\0')
			path_value = &path_value[cur_path_len + 1];
		else
			return (NULL);
	}
	return (NULL);
}

int		make_full_path(char **command, char *path_value)
{
	char	*full_command;

	if ((full_command = join_path_to_command(command[0], path_value)))
	{
		free(command[0]);
		command[0] = full_command;
		return (1);
	}
	return (0);
}

char	*get_path_from_environ(char **last_environ)
{
	char	*path_value;

	while (*last_environ)
	{
		if (ft_strncmp(*last_environ, "PATH=", 5) == 0)
		{
			path_value = &(*last_environ)[5];
			return (path_value);
		}
		last_environ++;
	}
	return (NULL);
}

int		make_exploitable(char **command, char **last_environ)
{
	char	*path_value;

	if (access(*command, F_OK) == 0)
		return (1);
	if (last_environ == NULL)
		return (0);
	if ((path_value = get_path_from_environ(last_environ)))
		return (make_full_path(command, path_value));
	return (0);
}
