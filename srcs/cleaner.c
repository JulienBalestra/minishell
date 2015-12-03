/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:02 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:03 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	remove_link(t_env *link)
{
	if (link)
	{
		free(link->name);
		link->name = NULL;
		free(link->value);
		link->value = NULL;
		free(link);
	}
}

void	delete_list(t_env **env)
{
	t_env *current;

	while (*env)
	{
		current = (*env)->next;
		remove_link(*env);
		*env = current;
	}
}

void	ft_str3del(char ***str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		ft_str2del(str[i]);
		i++;
	}
	free(str);
}

void	clean_program(t_sh *shell)
{
	delete_list(&(shell->env));
	ft_str2del(shell->l_env);
	free(shell->env);
	free(shell->ps1);
	if (shell->mock)
	{
		clean_program(shell->mock);
	}
	ft_str2del(shell->l_cmd);
	if (shell->buf)
	{
		free(shell->buf);
	}
	free(shell);
}
