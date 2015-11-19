#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int is_builtin_env_errors(t_be *benv)
{
	if (benv->unet == -1)
	{
		ft_putstr_fd("env: option requires an argument -- 'u'\n", 2);
		return (1);
	}
	else if (benv->null == 1 && benv->cmd == 1)
	{
		ft_putstr_fd("env: cannot specify --null (-0) with command\n", 2);
		return (1);
	}
	return (0);
}