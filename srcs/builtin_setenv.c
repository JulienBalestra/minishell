#include <stdlib.h>
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void add_new_env(t_env *env, char *name, char *value)
{
	t_env *new;

	if ((new = (t_env *)malloc(sizeof(t_env))))
	{
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->prev = env;
		env->next = new;
		new->next = NULL;
	}
}

void modify_env_value(t_env *browse, char *value)
{
	if (browse && value)
	{
		free(browse->value);
		browse->value = ft_strdup(value);
	}
}

void find_and_modify(char *name, char *value, t_sh *shell)
{
	t_env *browse;

	browse = shell->env;
	while (browse)
	{
		if (ft_strcmp(name, browse->name) == 0)
		{
			modify_env_value(browse, value);
			override_last_environ(shell);
			return;
		}
		if (browse->next)
			browse = browse->next;
		else
			break ;
	}
	add_new_env(browse, name, value);
	override_last_environ(shell);
}

void builtin_setenv(char **command, t_sh *shell)
{
	if (tab_len(command) < 3)
		return;
	else if (tab_len(command) != 3)
	{
		ft_putendl_fd("setenv: too many arguments", 2);
		return;
	}
	find_and_modify(command[1], command[2], shell);
}