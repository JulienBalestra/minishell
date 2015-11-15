#include "minishell.h"
#include <unistd.h>

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

#include <stdio.h>
#include <stdlib.h>

char *get_full_path(char *tail_path)
{
	char *full_path;

	full_path = NULL;
	(void) tail_path;
	return (full_path);
}

void change_dir(char *path, t_sh *shell)
{
	int ret;
	char *buf_wd;
	char *oldpwd;

	if ((buf_wd = (char *) malloc(sizeof(char) * 2048)))
	{
		oldpwd = getcwd(buf_wd, 2048);
		if ((ret = chdir(path)) == 0)
		{
			ft_setenv("OLDPWD", oldpwd, shell);
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