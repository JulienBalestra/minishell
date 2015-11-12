#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


char  *replace_last_command_return_code(char *dollar_question, t_sh *shell)
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


void manage_interpretor(char **command, t_sh *shell)
{
	int i;

	i = 0;
	if (shell)
	{
		while (command[i])
		{
			if (ft_strcmp(command[i], "$?") == 0)
			{

				command[i] = replace_last_command_return_code(command[i], shell);
			}
			i++;
		}
	}
}