#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


void builtin_exit(char **command, t_sh *shell)
{
	if (ft_str2len(command) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	if (ft_str2len(command) == 2)
		shell->last_command_ret = ft_atoi(command[1]);
	shell->exit = 1;
}