/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_symbolic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:41:46 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:41:47 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	native_full(char *path, char *old_pwd, t_sh *shell)
{
	if (chdir(path) == 0)
	{
		ft_setenv("OLDPWD", old_pwd, shell);
		shell->l_ret = 0;
		ft_setenv("PWD", path, shell);
	}
}

void	made_full(char *path, char *full, char *old_pwd, t_sh *shell)
{
	if (chdir(path) == 0)
	{
		ft_setenv("OLDPWD", old_pwd, shell);
		shell->l_ret = 0;
		ft_setenv("PWD", full, shell);
	}
	ft_strdel(&full);
}

void	just_path(char *path, char *old_pwd, t_sh *shell)
{
	char	*wd;

	if (chdir(path) == 0)
	{
		ft_setenv("OLDPWD", old_pwd, shell);
		shell->l_ret = 0;
		wd = triple_join(old_pwd, "/", path);
		ft_setenv("PWD", wd, shell);
		free(wd);
	}
}

void	cd_symblink(char *path, t_sh *shell)
{
	char	*old_pwd;
	char	*full;

	old_pwd = get_env_value("PWD", shell->env);
	full = NULL;
	if (ft_strstr(path, "..") || ft_strstr(path, "./"))
	{
		full = triple_join(old_pwd, "/", path);
		full = troncate_dots(full);
	}
	if (path[0] == '/' && !full)
		native_full(path, old_pwd, shell);
	else if (full)
		made_full(path, full, old_pwd, shell);
	else
		just_path(path, old_pwd, shell);
}
