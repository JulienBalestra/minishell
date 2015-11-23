#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

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
			display_not_such("cd", path);
		free(buf_wd);
	}
}

void change_dir(char *path, t_sh *shell)
{
	struct stat *stats;

	if (path && (stats = (struct stat *) malloc(sizeof(struct stat))))
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
			display_not_such("cd", path);
		free(stats);
	}
}

void builtin_cd(char **command, t_sh *shell)
{
	if (tab_len(command) == 1 || ft_strcmp(command[1], "~") == 0)
	{
		go_to_home_directory(shell);
	}
	else if (ft_strcmp(command[1], "-") == 0)
	{
		go_to_old_pwd(shell);
	}
	else
	{
		change_dir(command[1], shell);
	}
}