/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:10 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:11 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

void	display_environ(char **to_display, int end_line)
{
	if (!to_display)
		return ;
	while (*to_display)
	{
		ft_putstr(*to_display);
		if (end_line == 1)
			ft_putchar('\n');
		to_display++;
	}
}

void	display_only_setenv(char **command, int end_line)
{
	char	**mock;
	int		i;

	mock = get_mock_environ(command);
	i = 0;
	while (mock && mock[i])
	{
		if (is_setenv(mock[i]))
		{
			ft_putstr(mock[i]);
			if (end_line)
				ft_putchar('\n');
			else
				ft_putchar('\x00');
		}
		i++;
	}
	ft_str2del(mock);
}
