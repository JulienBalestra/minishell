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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

int 	make_pipe(const char **str, t_sh *shell, char **mock_environ, int mock)
{
	int		p[2];
	int		status;
	pid_t	pid;
	char	**ptr;
	char	*cmd[3];

	cmd[0] = "/bin/cat";
	cmd[1] = "-e";
	cmd[2] = NULL;
	pipe(p);
	pid = fork();
	if ((int)pid == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		ptr = (char **)str;
		execve(str[0], ptr, mock_environ);
		return (0);
	}
	else if ((int)pid > 0)
	{
		dup2(p[0], 0);
		close(p[1]);
		waitpid(-1, &status, 0);
		if (mock == 0)
			mock_environ = shell->l_env;
		//fd = open("redir", O_WRONLY | O_TRUNC | O_CREAT,
		//	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		//close(fd);
		execve(cmd[0], cmd, mock_environ);
		return (1);
	}
	ft_putstr("error\n");
	return (-1);
}

int		do_exec(const char **str, t_sh *shell, char **mock_environ, int mock)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		return (make_pipe(str, shell, mock_environ, mock));
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
