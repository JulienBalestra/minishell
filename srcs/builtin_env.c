#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void display_environ(char **to_display, int end_line)
{
	if (!to_display)
		return;
	while (*to_display)
	{
		ft_putstr(*to_display);
		if (end_line == 1)
			ft_putchar('\n');
		to_display++;
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

void unset_env(char **command, t_sh *shell)
{
	int i;
	int max;
	char **unset_ed;

	i = 0;
	max = tab_len(command);
	while (i < max && command[i])
	{
		if (ft_strcmp("-u", command[i]) == 0 && command[i + 1])
		{
			if ((unset_ed = build_tab_environ(shell->env, command[i + 1])))
			{
				if (command[i + 2])
				{
					ft_putendl("OKUNSET with command");
				}
				else
					display_environ(unset_ed, 1);
				tab_free(unset_ed);
			}
			else
				ft_putstr_fd("env: option requires an argument -- 'u'\n", 2);
			return;
		}
		i++;
	}
}

void builtin_env(char **command, t_sh *shell)
{
	char **ptr;

	if (tab_len(command) == 1)
		display_environ(shell->last_environ, 1);

	else if (tab_len(command) > 1 && (ft_strcmp("-u", command[1]) == 0))
		unset_env(command, shell);

	else if (tab_len(command) == 2 && (ft_strcmp("-0", command[1]) == 0 || ft_strcmp("--null", command[1]) == 0))
		display_environ(shell->last_environ, 0);

	else if (tab_len(command) == 2 && (ft_strcmp(command[1], "-i") != 0))
	{
		ptr = &command[1];
		trivial_env(ptr, shell, 0);
	}
	else if (tab_len(command) == 3 &&
			 (ft_strcmp(command[1], "-i") == 0 || ft_strcmp(command[1], "--ignore-environment") == 0))
	{
		ptr = &command[2];
		trivial_env(ptr, shell, 1);
	}
}