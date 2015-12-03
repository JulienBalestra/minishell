/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_interpretor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:44:26 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:44:27 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

int		is_d_var(char *variable)
{
	if (variable[0] == '$' && variable[1])
	{
		if (variable[1] != '{')
			return (1);
		else if (variable[ft_strlen(variable) - 1] == '}')
			return (2);
	}
	return (0);
}

int		is_dollar_builtin(char *entry)
{
	if (ft_strcmp(entry, "$?") == 0)
		return (1);
	if (ft_strcmp(entry, "$$") == 0)
		return (2);
	return (0);
}

char	*transform_dollar_builtin(char *entry, t_sh *shell)
{
	char	*new;

	if (is_dollar_builtin(entry) == 1)
		new = replace_dollar_question(entry, shell);
	else
		new = replace_dollar_dollar(entry);
	return (new);
}
