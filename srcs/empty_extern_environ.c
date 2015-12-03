/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_extern_environ.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:19 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:20 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_env	*manage_empty_environ(void)
{
	char	*buf_pwd;
	char	*string;
	t_env	*env;

	env = NULL;
	if ((buf_pwd = (char *)malloc(sizeof(char) * CWD)))
	{
		string = ft_strjoin("PWD=", getcwd(buf_pwd, CWD));
		env = create_env_link(env, string);
		free(buf_pwd);
		free(string);
	}
	return (env);
}
