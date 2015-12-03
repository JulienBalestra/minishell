/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:44:04 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:44:05 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		is_goto_home(char **command)
{
	size_t	len;

	len = ft_str2len(command);
	if (len == 1 || ft_strcmp(command[1], "~") == 0)
	{
		return (1);
	}
	else if (len == 2 && ft_strcmp(command[1], "-P") == 0)
	{
		return (1);
	}
	else if (len == 2 && ft_strcmp(command[1], "-L") == 0)
	{
		return (1);
	}
	return (0);
}

char	*strdup_skip(char *str)
{
	size_t	len;
	int		i;
	int		t;
	char	*dup;

	i = 0;
	t = 0;
	len = ft_strlen(str);
	if ((dup = (char *)malloc(sizeof(char) * (len + 1))))
	{
		while (str[i])
		{
			if (ft_strncmp("//", &str[i], 2))
			{
				dup[t] = str[i];
				t++;
			}
			i++;
		}
		dup[t] = '\0';
	}
	return (dup);
}

char	*remove_duplicate_slash(char *path)
{
	char	*ready;

	if (ft_strstr(path, "//"))
	{
		ready = strdup_skip(path);
		return (ready);
	}
	else
	{
		return (ft_strdup(path));
	}
}

char	*get_full_home(char *str, t_sh *shell)
{
	char	*full;
	char	*s1;
	char	*s2;
	char	*s3;
	int		len;

	s2 = get_env_value("HOME", shell->env);
	if (!s2)
		return (str);
	len = len_to_char(str, '~');
	s1 = ft_strndup(str, (size_t)len);
	s3 = ft_strdup(&str[len + 1]);
	full = triple_join(s1, s2, s3);
	ft_strdel(&s1);
	ft_strdel(&s3);
	ft_strdel(&str);
	return (full);
}

void	transform_tilde(char **command, t_sh *shell)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (is_tilde_transform(command[i], '~'))
		{
			command[i] = get_full_home(command[i], shell);
		}
		i++;
	}
}
