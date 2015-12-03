/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:36 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:37 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

char	**defrag(char **s, size_t len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp("..", s[i]) == 0 && i > 0)
		{
			ft_strdel(&s[i - 1]);
			ft_str2defrag(s, len);
			ft_strdel(&s[i - 1]);
			ft_str2defrag(s, len);
			i = 0;
		}
		else if (ft_strcmp(".", s[i]) == 0)
		{
			free(s[i]);
			s[i] = NULL;
			ft_str2defrag(s, len);
			i = 0;
		}
		else
			i++;
	}
	return (s);
}

char	*join_slash(char **s)
{
	int		i;
	char	*tmp;
	char	*str;

	str = ft_strjoin("/", s[0]);
	i = 1;
	while (s[i])
	{
		tmp = str;
		str = triple_join(tmp, "/", s[i]);
		ft_strdel(&tmp);
		i++;
	}
	ft_str2del(s);
	return (str);
}

char	*troncate_dots(char *path)
{
	char	**s;
	char	*str;

	if (path[0] == '/')
	{
		s = ft_lz_strsplit(&path[1], '/');
	}
	else
	{
		s = ft_lz_strsplit(&path[0], '/');
	}
	s = defrag(s, ft_str2len(s));
	str = join_slash(s);
	ft_strdel(&path);
	return (str);
}
