#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int manage_builtins(char **command, t_sh *shell)
{
	if (ft_strcmp(command[0], "env") == 0)
	{
		builtin_env(shell->last_environ);
		// TODO -> env args ?
		return (1);
	}
	else if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		builtin_unsetenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		builtin_exit(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "setenv") == 0)
	{
		builtin_setenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "getenv") == 0)
	{
		builtin_getenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "cd") == 0)
	{
		builtin_cd(command, shell);
		return (1);
	}
	return (0);
}