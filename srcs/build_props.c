#include <stdlib.h>
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_env *create_env_link(t_env *env, char *environ_entry)
{
	t_env *link;
	int len_until;

	if ((link = (t_env *) malloc(sizeof(t_env))))
	{
		len_until = strlen_until_char(environ_entry, '=');
		link->name = ft_strndup(environ_entry, (size_t) len_until);
		environ_entry = &environ_entry[len_until + 1];
		link->value = ft_strdup(environ_entry);
		link->next = NULL;
		if (env)
		{
			link->prev = env;
			env->next = link;
		}
		else
			link->prev = NULL;
		return (link);
	}
	return (NULL);
}

t_env *build_env_list(char **environ)
{
	t_env *env;

	env = NULL;
	if (tab_len(environ) == 0)
	{
		env = manage_empty_environ();
	}
	else
	{
		while (*environ)
		{
			if (ft_strncmp("OLDPWD", *environ, 6) != 0)
				env = create_env_link(env, *environ);
			environ++;
		}
	}
	while (env)
		if (env->prev)
			env = env->prev;
		else
			break ;
	return (env);
}

t_sh *create_shell_from(char **environ_tab)
{
	t_sh *shell;

	if ((shell = (t_sh *) malloc(sizeof(t_sh))))
	{
		shell->env = build_env_list(environ_tab);
		shell->mock = NULL;
		shell->last_environ = NULL;
		shell->last_environ = override_last_environ(shell);
		shell->prompt = ft_strdup(PROMPT);
		shell->len_prompt = ft_strlen(PROMPT);
		shell->last_command_ret = 0;
		shell->exit = 0;
		return (shell);
	}
	return (NULL);
}

t_sh *create_shell_props(void)
{
	t_sh *shell;
	extern char **environ;

	if ((shell = create_shell_from(environ)))
	{
		return (shell);
	}
	return (NULL);
}
