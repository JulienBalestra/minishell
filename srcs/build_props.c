/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_props.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:31:14 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:31:18 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_env		*create_env_link(t_env *env, char *environ_entry)
{
	t_env	*link;
	int		len_until;

	if ((link = (t_env *)malloc(sizeof(t_env))))
	{
		len_until = len_to_char(environ_entry, '=');
		link->name = ft_strndup(environ_entry, (size_t)len_until);
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

t_env		*build_env_list(char **environ)
{
	t_env	*env;

	env = NULL;
	if (ft_str2len(environ) == 0)
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
	return (get_start(env));
}

t_sh		*create_shell_from(char **environ_tab)
{
	t_sh	*shell;

	if ((shell = (t_sh *)malloc(sizeof(t_sh))))
	{
		shell->env = build_env_list(environ_tab);
		ensure_pwd(shell);
		shell->mock = NULL;
		shell->l_env = NULL;
		shell->l_env = override_last_environ(shell);
		shell->ps1 = ft_strdup(PROMPT);
		shell->len_ps1 = ft_strlen(PROMPT);
		shell->l_ret = 0;
		shell->l_cmd = NULL;
		shell->buf = NULL;
		shell->exit = 0;
		return (shell);
	}
	return (NULL);
}

t_sh		*create_shell_props(void)
{
	t_sh		*shell;
	extern char	**environ;

	if ((shell = create_shell_from(environ)))
	{
		return (shell);
	}
	return (NULL);
}
