/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:43:33 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:43:34 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_env	*get_start(t_env *env)
{
	while (env)
	{
		if (env->prev)
			env = env->prev;
		else
			break ;
	}
	return (env);
}

t_env	*get_end(t_env *env)
{
	while (env)
	{
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (env);
}

t_env	*get_env_by_value(char *name, t_env *env)
{
	env = get_start(env);
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

t_env	*upsert_link(t_env *env, char *environ_entry)
{
	t_env	*link;
	int		len_until;
	char	*name;

	len_until = len_to_char(environ_entry, '=');
	name = ft_strndup(environ_entry, (size_t)len_until);
	if ((link = get_env_by_value(name, env)))
	{
		if (link->value)
			free(link->value);
		environ_entry = &environ_entry[len_until + 1];
		link->value = ft_strdup(environ_entry);
	}
	else
		env = create_env_link(env, environ_entry);
	free(name);
	return (env);
}
