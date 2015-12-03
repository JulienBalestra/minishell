/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:41:54 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:41:55 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char	*concat_chdir(char *path, t_sh *shell)
{
	char	*dirs;
	char	*full;
	char	**dir_l;
	int		i;

	if ((dirs = get_env_value("CHDIR", shell->env)))
	{
		dir_l = ft_lz_strsplit(dirs, ':');
		i = 0;
		while (dir_l[i])
		{
			full = triple_join(dir_l[i], "/", path);
			if (access(full, F_OK) == 0)
			{
				ft_str2del(dir_l);
				return (full);
			}
			ft_strdel(&full);
			i++;
		}
		ft_str2del(dir_l);
	}
	return (NULL);
}

char	*create_chdir_path(char *path, t_sh *shell)
{
	char	*good;

	if (access(path, F_OK) == 0)
		return (ft_strdup(path));
	if ((good = concat_chdir(path, shell)))
		return (good);
	return (ft_strdup(path));
}
