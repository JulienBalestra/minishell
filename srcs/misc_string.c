/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:19 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:20 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../libft/includes/libft.h"

int		is_tilde_transform(char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (str[i] != '~')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n == 1 ? 1 : 0);
}

char	*triple_join(char *s1, char *s2, char *s3)
{
	char	*final;
	int		i;

	i = 0;
	if ((final = (char *)malloc(sizeof(char) * ft_nstrlen(s1) +
										ft_nstrlen(s2) + ft_nstrlen(s3) + 1)))
	{
		while (*s1)
		{
			final[i++] = *s1;
			s1++;
		}
		while (*s2)
		{
			final[i++] = *s2;
			s2++;
		}
		while (s3 && *s3)
		{
			final[i++] = *s3;
			s3++;
		}
		final[i] = '\0';
	}
	return (final);
}

void	convert_chars(char *str)
{
	while (*str)
	{
		if (*str == '\t' || *str == '\b' || *str == '\n' ||
				*str == '\r' || *str == '\f')
			*str = ' ';
		str++;
	}
}

int		ft_converter(const char *nptr, int sign)
{
	int	result;

	result = 0;
	while (*nptr != '\0' && *nptr > 47 && *nptr < 58)
	{
		result = result * 10 + *nptr - 48;
		nptr++;
	}
	if (sign < 0)
		result = -result;
	if (*nptr)
		return (result + 1);
	return (result);
}

int		cust_atoi(const char *nptr)
{
	int	sign;

	sign = 0;
	while (*nptr != '\0' && sign == 0 &&
		(*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\r'
			|| *nptr == '\f' || *nptr == '\v'
			|| *nptr == '+' || *nptr == '-'))
	{
		if (*nptr == '+')
			sign++;
		else if (*nptr == '-')
			sign--;
		nptr++;
	}
	return (ft_converter(nptr, sign));
}
