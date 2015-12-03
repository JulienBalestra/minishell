/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:56 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:57 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_nothing(void)
{
	;
}

int		run_each_cli(char ***command, t_sh *shell)
{
	int	i;

	i = 0;
	while (shell->exit == 0 && command && command[i])
	{
		manage_interpretor(command[i], shell);
		if (manage_builtins(command[i], shell))
			do_nothing();
		else if (make_exploitable(command[i], shell->l_env))
		{
			if (do_fork((const char **)command[i], shell, NULL, 0) == 1)
				return (1);
		}
		else
			display_command_not_found(command[i][0]);
		i++;
	}
	return (0);
}

int		process_cli(t_sh *shell)
{
	char	***command;

	if (existing_line(shell) && correct_syntax(shell))
	{
		command = build_command(shell);
		if (run_each_cli(command, shell) == 1)
			return (1);
		ft_str3del(command);
	}
	return (0);
}

int		start_engine(t_sh *shell)
{
	while (42)
	{
		shell->buf = get_line(shell);
		if (process_cli(shell) == 1)
			return (1);
		if (shell->exit == 1)
			return (0);
	}
}

int		main(void)
{
	int		ret;
	t_sh	*shell;

	if ((shell = create_shell_props()))
	{
		if (start_engine(shell) == 0)
		{
			ret = shell->l_ret;
			clean_program(shell);
			return (ret);
		}
		return (2);
	}
	return (3);
}
