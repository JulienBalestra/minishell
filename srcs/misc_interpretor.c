#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

int is_$var(char *variable)
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

int is_dollar_builtin(char *entry)
{
	if (ft_strcmp(entry, "$?") == 0)
		return (1);
	if (ft_strcmp(entry, "$$") == 0)
		return (2);
	return (0);
}

char *transform_dollar_builtin(char *entry, t_sh *shell)
{
	char *new;

	if (is_dollar_builtin(entry) == 1)
		new = replace_dollar_question(entry, shell);
	else
		new = replace_dollar_dollar(entry);

	return (new);
}