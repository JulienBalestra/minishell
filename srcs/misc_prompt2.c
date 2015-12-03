/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_prompt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:00 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:01 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../libft/includes/libft.h"

void	display_cd_invalid_option(char *opt)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(opt, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("cd: usage: cd [-L OR -P] [dir]\n", 2);
}

void	display_cd_permission(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
