#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void display_last_environ(char **last_environ, int end_line)
{
	while (last_environ && *last_environ)
	{
		ft_putstr(*last_environ);
		if (end_line == 1)
			ft_putchar('\n');
		last_environ++;
	}
}

void trivial_env(char **command, t_sh *shell, int mock)
{
	if (make_exploitable(command, shell->last_environ))
	{
		if (pass_str_to_exec((const char **) command, shell, NULL, mock) == 1)
			return;
	}
	else
		display_command_not_found(command[0]);
}

void builtin_env(char **command, t_sh *shell)
{
	char **ptr;

	if (tab_len(command) == 1)
		display_last_environ(shell->last_environ, 1);
	else if (tab_len(command) == 2 && (ft_strcmp("-0", command[1]) == 0 || ft_strcmp("--null", command[1]) == 0))
		display_last_environ(shell->last_environ, 0);
	else if (tab_len(command) == 2 && (ft_strcmp(command[1], "-i") != 0))
	{
		ptr = &command[1];
		trivial_env(ptr, shell, 0);
	}
	else if (tab_len(command) == 3 && (ft_strcmp(command[1], "-i") == 0))
	{
		ptr = &command[2];
		trivial_env(ptr, shell, 1);
	}
}