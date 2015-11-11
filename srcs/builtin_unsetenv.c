#include <stdlib.h>
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void destroy_env_link(t_env *env)
{
	if (env)
	{
		free(env->name);
		free(env->value);
		free(env);
	}
}

void remove_env_link(t_sh *shell, t_env *env)
{
	t_env *previous;

	if (env)
	{
		if (env->prev)
		{
			previous = env->prev;
			if (env->next)
			{
				previous->next = env->next;
				env->next->prev = previous;
			}
			else
				previous->next = NULL;
		}
		else
		{
			shell->env = env->next;
			env->next->prev = NULL;
		}
		destroy_env_link(env);
	}
}

void find_and_destroy(char *name, t_sh *shell)
{
	t_env *browse;

	browse = shell->env;
	while (browse)
	{
		if (ft_strcmp(name, browse->name) == 0)
		{
			remove_env_link(shell, browse);
			override_last_environ(shell);
			return;
		}
		browse = browse->next;
	}
}

void builtin_unsetenv(char **command, t_sh *shell)
{
	if (tab_len(command) == 1)
		return;
	command++;
	while (*command)
	{
		find_and_destroy(*command, shell);
		command++;
	}
}