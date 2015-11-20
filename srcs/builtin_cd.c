#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "minishell.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void cd_symblink(char *path, t_sh *shell)
{
	// TODO
	(void) path;
	(void) shell;
}

void cd_physical(char *path, t_sh *shell)
{
	int ret;
	char *buf_wd;
	char *old_pwd;

	if ((buf_wd = (char *) malloc(sizeof(char) * 2048)))
	{
		old_pwd = getcwd(buf_wd, 2048);
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", old_pwd, shell);
			shell->last_command_ret = ret;
			ft_setenv("PWD", getcwd(buf_wd, 2048), shell);
		}
		else
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			shell->last_command_ret = 1;
		}
		free(buf_wd);
	}
}

void change_dir(char *path, t_sh *shell)
{
	struct stat *stats;

	if ((stats = (struct stat *) malloc(sizeof(struct stat))))
	{
		if (lstat(path, stats) == 0)
		{
			cd_physical(path, shell); //TODO ->
			/*
			if (S_ISLNK(stats->st_mode))
				cd_symblink(path, shell);
			else
				cd_physical(path, shell);*/
		}
		else
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			shell->last_command_ret = 1;
		}
		free(stats);
	}
}

void builtin_cd(char **command, t_sh *shell)
{
	if (tab_len(command) == 1 || ft_strcmp(command[1], "~") == 0)
		change_dir(get_env_value("HOME", shell->env), shell);
	else if (ft_strcmp(command[1], "-") == 0)
	{
		if (get_env_value("OLDPWD", shell->env) == NULL)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			shell->last_command_ret = 1;
			return;
		}
		change_dir(get_env_value("OLDPWD", shell->env), shell);
		ft_putendl(get_env_value("PWD", shell->env));
	}
	else
	{
		change_dir(command[1], shell);
	}
}