#include <stdlib.h>
#include "minishell.h"

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

static size_t len_env(t_env *env)
{
	size_t len;

	len = 0;
	while (env)
	{
		env = env->next;
		len++;
	}
	return (len);
}

char **build_tab_environ(t_env *env)
{
	char **last_environ;
	int i;

	i = 0;
	if ((last_environ = (char **) malloc(sizeof(char *) * (len_env(env) + 1))))
	{
		while (env)
		{
			last_environ[i] = triple_join(env->name, "=", env->value);
			i++;
			env = env->next;
		}
		last_environ[i] = NULL;
	}
	return (last_environ);
}

char **override_last_environ(t_sh *shell)
{
	tab_free(shell->last_environ);
	return (build_tab_environ(shell->env));
}