#include "libft.h"

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

char **get_mock_environ(char **command)
{
	char **mock;
	t_env *cenv;
	int i;

	cenv = NULL;
	i = 0;
	while (command[i])
	{
		if (ft_strchr(command[i], '='))
			cenv = upsert_link(cenv, command[i]);
		i++;
	}
	cenv = get_start(cenv);
	mock = build_tab_environ(cenv);
	delete_list(&cenv);
	return (mock);
}

char **get_command(char **command)
{
	int i;
	int u;

	i = 1;
	u = 0;
	while (command[i])
	{
		if (u == 0 && (is_ignore_arg(command[i]) || is_null_arg(command[i])))
			i++;
		else if (u == 0 && ft_strcmp(command[i], "-u") == 0 && command[i + 1])
			i = i+ 2;
		else if (is_setenv(command[i]))
		{
			u = 1;
			i++;
		}
		else
			break;
	}
	return (&command[i]);
}

void run_under_new_environ(char **command, t_sh *shell)
{
	char **mock;
	char **ptr;

	mock = get_mock_environ(command);
	ptr = get_command(command);
	if (make_exploitable(ptr, mock))
	{
		if (pass_str_to_exec((const char **) ptr, shell, mock, 1) == 1)
			return;
	}
	else
		display_not_such("env", ptr[0]);
	tab_free(mock);
}

void run_under_alter_environ(char **command, t_sh *shell)
{
	char **new;
	char **merge;
	char **ptr;

	new = get_mock_environ(command);
	merge = merge_both_environ(shell->last_environ, command, new);
	tab_free(new);
	ptr = get_command(command);
	if (make_exploitable(ptr, merge))
	{
		if (pass_str_to_exec((const char **) ptr, shell, merge, 1) == 1)
			return;
	}
	else
		display_not_such("env", ptr[0]);
	tab_free(merge);
}

void alter_environ_and_display(char **command, t_sh *shell, int end_lines)
{
	char **new;
	char **merge;

	new = get_mock_environ(command);
	merge = merge_both_environ(shell->last_environ, command, new);
	tab_free(new);
	display_environ(merge, end_lines);
	tab_free(merge);
}