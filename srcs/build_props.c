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
	while (*environ)
	{
		env = create_env_link(env, *environ);
		environ++;
	}
	while (env)
		if (env->prev)
			env = env->prev;
		else
			break ;
	return (env);
}

char **tab_dup(char **tab)
{
	char **new_tab;
	char **begin_tab;

	begin_tab = NULL;
	if ((new_tab = (char **) malloc(sizeof(char *) * (tab_len(tab) + 1))))
	{
		begin_tab = new_tab;
		while (*tab)
		{
			*new_tab = strdup(*tab);
			new_tab++;
			tab++;
		}
		*new_tab = NULL;
	}
	return (begin_tab);
}

t_sh *create_shell_props(void)
{
	t_sh *shell;
	extern char **environ;

	if ((shell = (t_sh *) malloc(sizeof(t_sh))))
	{
		shell->env = build_env_list(environ);
		shell->last_environ = tab_dup(environ);
		shell->prompt = ft_strdup(PROMPT);
		shell->len_prompt = ft_strlen(PROMPT);
		shell->last_command_ret = 0;
		return (shell);
	}
	return (NULL);
}
