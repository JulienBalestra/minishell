#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


int manage_builtins(char **command, t_sh *shell)
{
	if (ft_strcmp(command[0], "env") == 0)
	{
		builtin_env(shell->last_environ);
		return (1);
	}
	return (0);
}