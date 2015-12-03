/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:43:55 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:43:58 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

t_env	*upsert_from_tab(t_env *uenv, char **tab)
{
	while (*tab)
	{
		if (ft_strchr(*tab, '='))
			uenv = upsert_link(uenv, *tab);
		tab++;
	}
	return (uenv);
}

t_env	*cut_list(t_env *env)
{
	t_env	*previous;
	t_env	*next_one;

	previous = NULL;
	next_one = NULL;
	if (env->prev)
	{
		previous = env->prev;
		if (env->next)
		{
			next_one = env->next;
			previous->next = env->next;
			next_one->prev = previous;
		}
		else
			previous->next = NULL;
	}
	else
	{
		next_one = env->next;
		if (next_one)
			next_one->prev = NULL;
	}
	destroy_env_link(env);
	return (previous ? previous : next_one);
}

t_env	*find_and_cut(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			env = cut_list(env);
		}
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (get_start(env));
}

t_env	*unset_elem(t_env *env, char **unset)
{
	int	i;

	i = 0;
	while (unset[i])
	{
		if (ft_strcmp(unset[i], "-u") == 0 && unset[i + 1])
		{
			env = find_and_cut(env, unset[i + 1]);
			i = i + 2;
		}
		else
			i++;
	}
	return (env);
}

char	**merge_both_environ(char **first, char **unset, char **second)
{
	char	**merge;
	t_env	*menv;

	menv = NULL;
	menv = upsert_from_tab(menv, first);
	menv = get_start(menv);
	menv = unset_elem(menv, unset);
	menv = get_end(menv);
	menv = upsert_from_tab(menv, second);
	menv = get_start(menv);
	merge = build_tab_environ(menv);
	delete_list(&menv);
	return (merge);
}
