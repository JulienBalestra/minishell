/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:28 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:29 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		is_benv_errors(t_be *benv)
{
	if (benv->unet == -1)
	{
		ft_putstr_fd("env: option requires an argument -- 'u'\n", 2);
		return (1);
	}
	else if (benv->null == 1 && benv->cmd == 1)
	{
		ft_putstr_fd("env: cannot specify --null (-0) with command\n", 2);
		return (1);
	}
	return (0);
}

int		is_benv_do_nothing(t_be *benv)
{
	if (benv->ignore == 1 && benv->cmd == 0 && benv->set == 0)
		return (1);
	return (0);
}
