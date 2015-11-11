#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void builtin_env(char **last_environ)
{
	while (*last_environ)
	{
		ft_putendl(*last_environ);
		last_environ++;
	}
}