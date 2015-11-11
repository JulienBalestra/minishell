#include <stdlib.h>
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


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

static char **new_last_environ(t_env *env)
{
	char **last_environ;
	int i;

	i = 0;
	if ((last_environ = (char **) malloc(sizeof(char *) * (len_env(env) + 1))))
	{
		while (env)
		{
			last_environ[i] = triple_join(env->name, "=", env->value);
			env = env->next;
			i++;
		}
		last_environ[i] = NULL;
	}
	return (last_environ);
}

void override_last_environ(t_sh *shell)
{
	tab_free(shell->last_environ);
	shell->last_environ = new_last_environ(shell->env);
}