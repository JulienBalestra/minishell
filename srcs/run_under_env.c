#include "libft.h"

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

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

char **merge_both_environ(char **first, char **second)
{
	char **merge;
	t_env *menv;

	menv = NULL;
	while (*first)
	{
		if (ft_strchr(*first, '='))
			menv = upsert_link(menv, *first);
		first++;
	}
	while (*second)
	{
		if (ft_strchr(*second, '='))
			menv = upsert_link(menv, *second);
		second++;
	}
	menv = get_start(menv);
	merge = build_tab_environ(menv);
	delete_list(&menv);
	return (merge);
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

void run_under_alter_environ(char **command, t_sh *shell)
{
	char **new;
	char **merge;
	char **ptr;

	new = get_mock_environ(command);
	merge = merge_both_environ(shell->last_environ, new);
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