/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_getenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:38:23 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:38:24 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char		*get_env_value(char *name, t_env *env)
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

void		builtin_getenv(char **command, t_sh *shell)
{
	char	*value;

	if (ft_str2len(command) < 2)
		return ;
	else if (ft_str2len(command) != 2)
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
