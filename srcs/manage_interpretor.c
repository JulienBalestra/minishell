#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


char *replace_dollar_question(char *dollar_question, t_sh *shell)
{
	char *str_ret;

	if (dollar_question)
	{
		if ((str_ret = ft_itoa(shell->last_command_ret)))
		{
			free(dollar_question);
			return (str_ret);
		}
		else
			return (dollar_question);
	}
	return (NULL);
}

char *replace_dollar_dollar(char *dollar_question)
{
	char *str_ret;

	if (dollar_question)
	{
		if ((str_ret = ft_itoa((int) getpid())))
		{
			free(dollar_question);
			return (str_ret);
		}
		else
			return (dollar_question);
	}
	return (NULL);
}

char *replace_variable(char *name, t_sh *shell, int var_mode)
{
	char *str_ret;
	int i;

	i = 1;
	if (name)
	{
		if (var_mode == 2)
		{
			name[ft_strlen(name) - 1] = '\0';
			i++;
		}
		str_ret = get_env_value(&name[i], get_start(shell->env));
		free(name);
		return (ft_strdup(str_ret));
	}
	return (NULL);
}

void manage_interpretor(char **command, t_sh *shell)
{
	int i;
	int q;
	int len;

	i = 0;
	q = 0;
	if (shell && command)
	{
		len = ft_str2len(command);
		while (command[i])
		{
			// TODO remove quotes or manage split by quotes or blanks
			if (handle_quotes(command[i]) == 2)
			{
				command[i] = remove_quotes(command[i]);
				q = 1;
			}
			if (q == 0 && handle_quotes(command[i]) == 1)
				command[i] = remove_quotes(command[i]);
			else if (is_dollar_builtin(command[i]))
				command[i] = transform_dollar_builtin(command[i], shell);
			else if (is_$var(command[i]))
				command[i] = replace_variable(command[i], shell, is_$var(command[i]));
			i++;
			q = 0;
		}
		replace_null(command, len);
	}
}