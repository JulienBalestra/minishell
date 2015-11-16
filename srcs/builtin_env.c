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

void builtin_env(char **command, t_sh *shell)
{
	char **no_env;

	if (tab_len(command) == 1)
		display_last_environ(shell->last_environ, 1);
	else if (tab_len(command) == 2 &&
			 (ft_strcmp("-0", command[1]) == 0 ||
			  ft_strcmp("--null", command[1]) == 0))
		display_last_environ(shell->last_environ, 0);
	else if (tab_len(command) == 2)
	{
		no_env = command;
		if (make_exploitable(++no_env, shell->last_environ))
		{
			if (pass_str_to_exec((const char **) no_env, shell, NULL) == 1)
				return;
		}
		else
			display_command_not_found(no_env[0]);
	}
}