/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:43:13 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:43:14 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		is_exec(const char *command)
{
	struct stat	*st;

	if (access(command, X_OK) == 0)
	{
		if (command && (st = (struct stat *)malloc(sizeof(struct stat))))
		{
			if (stat(command, st) == 0)
			{
				if (S_ISDIR(st->st_mode))
				{
					display_is_directory(command);
					free(st);
					return (0);
				}
			}
			free(st);
			return (1);
		}
	}
	display_permission_denied(command);
	return (0);
}

int		do_exec(const char **str, t_sh *shell, char **mock_environ, int mock)
{
	int		status;
	char	**ptr;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		ptr = (char **)str;
		if (mock == 0)
			mock_environ = shell->l_env;
		execve(str[0], ptr, mock_environ);
		return (1);
	}
	else if (pid > 0)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->l_ret = WEXITSTATUS(status);
		return (0);
	}
	write(2, "error", 5);
	return (-1);
}

int		do_fork(const char **str, t_sh *shell, char **mock_environ, int mock)
{
	if (is_exec(str[0]) == 0)
		return (0);
	ft_str2del(shell->l_cmd);
	return (do_exec(str, shell, mock_environ, mock));
}
