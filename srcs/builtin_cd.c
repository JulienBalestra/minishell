#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "minishell.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void cd_symblink(char *path, t_sh *shell)
{
	int ret;
	char *wd;
	char *old_pwd;
	char *full;

	old_pwd = get_env_value("PWD", shell->env);
	full = NULL;
	// TODO if parent is LINK and command .. : troncate
	// TODO maybe create a struct entry ?
	if (ft_strstr(path, "..") || ft_strstr(path, "./"))
	{
		full = triple_join(old_pwd, "/", path);
		full = troncate_dots(full);
	}
	if (path[0] == '/' && ! full)
	{
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", old_pwd, shell);
			shell->l_ret = ret;
			ft_setenv("PWD", path, shell);
		}
	}
	else if (full)
	{
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", old_pwd, shell);
			shell->l_ret = ret;
			ft_setenv("PWD", full, shell);
		}
		free(full);
	}
	else
	{
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", old_pwd, shell);
			shell->l_ret = ret;
			wd = triple_join(old_pwd, "/", path);
			ft_setenv("PWD", wd, shell);
			free(wd);
		}
	}
}

void cd_physical(char *path, t_sh *shell)
{
	int ret;
	char *buf_wd;
	char *old_pwd;

	if ((buf_wd = (char *) malloc(sizeof(char) * CWD)))
	{
		old_pwd = get_env_value("PWD", shell->env);
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", old_pwd, shell);
			shell->l_ret = ret;
			ft_setenv("PWD", getcwd(buf_wd, CWD), shell);
		}
		else
		{
			display_not_such("cd", path);
		}
		free(buf_wd);
	}
}

void change_dir(char *path, t_sh *shell, int p)
{
	struct stat *st;

	if (path && (st = (struct stat *) malloc(sizeof(struct stat))))
	{
		if (ft_strlen(path) > 2)
			ft_remove_endchar(path, '/');
		if (lstat(path, st) == 0)
		{
			if (S_ISLNK(st->st_mode) && p == 0)
				cd_symblink(path, shell);
			else
				cd_physical(path, shell);
		}
		else
			display_not_such("cd", path); // TODO manage access rights
		free(st);
	}
}

void ensure_pwd(t_sh *shell)
{
	char *buf_wd;

	if (get_env_value("PWD", shell->env))
	{
		return;
	}
	if ((buf_wd = (char *) malloc(sizeof(char) * CWD)))
	{
		ft_setenv("PWD", getcwd(buf_wd, CWD), shell);
		free(buf_wd);
	}
}

void builtin_cd(char **command, t_sh *shell)
{
	char *ready;

	ensure_pwd(shell);
	transform_tilde(command, shell);
	if (is_goto_home(command))
	{
		go_to_home_directory(shell);
	}
	else if (ft_strcmp(command[1], "-") == 0)
	{
		go_to_old_pwd(shell);
	}
	else if (ft_strcmp(command[1], "-P") == 0)
	{
		change_dir(command[2], shell, 1); // <TODO cd -P -> != <cd ->
	}
	else if (ft_strcmp(command[1], "-L") == 0)
	{
		ready = remove_duplicate_slash(command[2]);
		change_dir(ready, shell, 0);
		free(ready);
	}
	else
	{
		// TODO only remove duplicate slashs if is an symblink
		ready = remove_duplicate_slash(command[1]);
		change_dir(ready, shell, 0);
		free(ready);
	}
}