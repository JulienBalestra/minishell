#include "libft.h"

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

void run_under_no_environ(char **ptr, t_sh *shell)
{
	if (make_exploitable(ptr, NULL))
	{
		if (pass_str_to_exec((const char **) ptr, shell, NULL, 1) == 1)
			return;
	}
	else
		display_not_such("env", ptr[0]);
}

char **get_mock_environ(char **command)
{
	char **mock;
	t_env *cenv;

	cenv = NULL;
	while (*command)
	{
		if (ft_strchr(*command, '='))
			cenv = upsert_link(cenv, *command);

		command++;
	}
	cenv = get_start(cenv);
	mock = build_tab_environ(cenv);
	delete_list(&cenv);
	return (mock);
}

char **get_command(char **command)
{
	int i;

	i = 1;
	while (command[i])
	{
		if (is_ignore_arg(command[i]) || is_null_arg(command[i]))
			i++;
		else if (ft_strcmp(command[i], "-u") == 0 && command[i + 1])
			i = i+ 2;
		if (is_setenv(command[i]))
			i++;
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
