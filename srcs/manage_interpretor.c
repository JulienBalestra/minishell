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
		if ((str_ret = ft_itoa((int)getpid())))
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

int is_var(char *variable)
{
	if (variable[0] == '$' && variable[1])
	{
		if (variable[1] != '{')
			return (1);
		else if (variable[ft_strlen(variable) - 1] == '}')
			return (2);
	}
	return (0);
}

void manage_interpretor(char **command, t_sh *shell)
{
	int i;

	i = 0;
	if (shell && command)
	{
		while (command[i])
		{
			if (ft_strcmp(command[i], "$?") == 0)
				command[i] = replace_dollar_question(command[i], shell);
			else if (ft_strcmp(command[i], "$$") == 0)
				command[i] = replace_dollar_dollar(command[i]);
			else if (is_var(command[i]))
				command[i] = replace_variable(command[i], shell, is_var(command[i]));
			i++;
		}
	}
}