/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:37:41 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:37:43 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	process_return_code(char **command, t_sh *shell)
{
	int	ret;

	ret = cust_atoi(command[1]);
	if (ret == ft_atoi(command[1]))
	{
		shell->l_ret = ret;
		if (ft_str2len(command) > 2)
		{
			ft_putendl_fd("exit: too many arguments", 2);
		}
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->l_ret = 2;
	}
}

void	builtin_exit(char **command, t_sh *shell)
{
	if (ft_str2len(command) > 1)
	{
		process_return_code(command, shell);
	}
	shell->exit = 1;
}
