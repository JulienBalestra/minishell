/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:55 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:56 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	ft_remove_endchar(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 1] == c)
		str[len - 1] = '\0';
}

char	*get_string_ready(char *buf)
{
	char	*str1;
	char	*str2;

	ft_remove_endchar(buf, '\n');
	convert_chars(buf);
	str1 = ft_remove_useless(buf, ' ');
	ft_remove_endchar(str1, ';');
	str2 = ft_remove_useless(str1, ' ');
	ft_strdel(&str1);
	return (str2);
}

int		next_char_is_semi(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == ';')
		{
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int		is_exploitable(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && str[i] == ';')
		{
			return (0);
		}
		if (i != 0 && str[i] == ';' && next_char_is_semi(&str[i + 1]))
		{
			return (0);
		}
		if (str[ft_strlen(str) - 1] == ';')
			return (0);
		i++;
	}
	return (1);
}

int		correct_syntax(t_sh *shell)
{
	char	*ready;
	int		ret;

	ready = get_string_ready(shell->buf);
	ret = is_exploitable(ready);
	ft_strdel(&shell->buf);
	shell->buf = ready;
	if (ret == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
		ft_strdel(&shell->buf);
		shell->l_ret = 2;
	}
	return (ret);
}
