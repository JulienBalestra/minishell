#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char *get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void builtin_getenv(char **command, t_sh *shell)
{
	char *value;

	if (tab_len(command) < 2)
		return ;
	else if (tab_len(command) != 2)
	{
		ft_putendl_fd("getenv: too many arguments", 2);
		return ;
	}
	if ((value = get_env_value(command[1], shell->env)))
	{
		ft_putstr(value);
	}
	ft_putstr("\n");
}