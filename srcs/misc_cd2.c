/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:44:16 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:44:18 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char	*create_cwd(t_sh *shell)
{
	char	*wd;

	if (shell && (wd = get_env_value("PWD", shell->env)))
	{
		wd = ft_strdup(wd);
	}
	else if ((wd = malloc(sizeof(char) * CWD)))
	{
		wd = getcwd(wd, CWD);
	}
	return (wd);
}
