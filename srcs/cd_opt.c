/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:41:30 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:41:31 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

int		operate_legal_opts(char **str)
{
	size_t	i;
	int		o;

	i = 1;
	o = 0;
	while (str[i])
	{
		if (str[i][0] == '-' && !is_minus(str[i]))
		{
			if ((is_physical(str[i]) || is_logical(str[i])) && o == 0)
				o++;
			else if (o && (is_physical(str[i]) || is_logical(str[i])))
				return (0);
			else
			{
				display_cd_invalid_option(str[i]);
				return (-1);
			}
		}
		else
			return (1);
		i++;
	}
	return (1);
}

int		is_legal_options(char **str, t_sh *shell)
{
	int		ret;

	ret = operate_legal_opts(str);
	if (ret == 0)
	{
		ft_putstr_fd("cd: usage: cd [-L OR -P] [dir]\n", 2);
		shell->l_ret = 1;
		return (0);
	}
	if (ret == -1)
	{
		shell->l_ret = 2;
		return (0);
	}
	return (1);
}

int		is_logical_goto_oldpwd(char **str)
{
	size_t	len;

	len = ft_str2len(str);
	if (len == 1)
		return (0);
	if (ft_strcmp("-", str[1]) == 0)
		return (1);
	if (len == 2)
		return (0);
	if (ft_strcmp("-L", str[1]) == 0 && ft_strcmp("-", str[2]) == 0)
		return (1);
	return (0);
}

int		is_physical_goto_oldpwd(char **str)
{
	size_t	len;

	len = ft_str2len(str);
	if (len == 1)
		return (0);
	if (ft_strcmp("-", str[1]) == 0)
		return (0);
	if (len == 2)
		return (0);
	if (ft_strcmp("-P", str[1]) == 0 && ft_strcmp("-", str[2]) == 0)
		return (1);
	return (0);
}
