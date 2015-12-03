/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:33:28 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:33:32 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "minishell.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void		cd_physical(char *path, t_sh *shell)
{
	int		ret;
	char	*buf_wd;
	char	*old_pwd;

	if ((buf_wd = (char *)malloc(sizeof(char) * CWD)))
	{
		old_pwd = get_env_value("PWD", shell->env);
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", old_pwd, shell);
			shell->l_ret = ret;
			ft_setenv("PWD", getcwd(buf_wd, CWD), shell);
		}
		else
			display_cd_permission(path);
		free(buf_wd);
	}
}

int			is_diff_cwd(t_sh *shell)
{
	char	*sys;
	char	*var;
	int		ret;

	ret = 1;
	if ((sys = malloc(sizeof(char) * CWD)))
	{
		sys = getcwd(sys, CWD);
		var = get_env_value("PWD", shell->env);
		if (sys && var && ft_strcmp(sys, var) == 0)
			ret = 0;
		ft_strdel(&sys);
	}
	return (ret);
}

void		change_dir(char *path, t_sh *shell, int p)
{
	struct stat	*st;
	char		*ready;

	if (path && (st = (struct stat *)malloc(sizeof(struct stat))))
	{
		path = create_chdir_path(path, shell);
		if (lstat(path, st) == 0)
		{
			if (p == 0 && (S_ISLNK(st->st_mode)))
			{
				if (ft_strlen(path) > 2)
					ft_remove_endchar(path, '/');
				ready = remove_duplicate_slash(path);
				cd_symblink(ready, shell);
				ft_strdel(&ready);
			}
			else
				cd_physical(path, shell);
		}
		else
			display_not_such("cd", path);
		free(st);
		ft_strdel(&path);
	}
}

void		ensure_pwd(t_sh *shell)
{
	char	*buf_wd;

	if (get_env_value("PWD", shell->env))
	{
		return ;
	}
	if ((buf_wd = (char *)malloc(sizeof(char) * CWD)))
	{
		ft_setenv("PWD", getcwd(buf_wd, CWD), shell);
		free(buf_wd);
	}
}

void		builtin_cd(char **command, t_sh *shell)
{
	ensure_pwd(shell);
	transform_tilde(command, shell);
	if (is_legal_options(command, shell) == 0)
		return ;
	if (is_goto_home(command))
		go_to_home_directory(shell);
	else if (is_logical_goto_oldpwd(command))
		go_to_old_pwd(shell, 0);
	else if (is_physical_goto_oldpwd(command))
		go_to_old_pwd(shell, 1);
	else if (ft_strcmp(command[1], "-P") == 0)
		change_dir(command[2], shell, 1);
	else if (ft_strcmp(command[1], "-L") == 0)
		change_dir(command[2], shell, 0);
	else
		change_dir(command[1], shell, 0);
}
