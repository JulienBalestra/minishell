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

char *remove_quotes(char *entry)
{
	char *new;

	new = ft_strndup(&entry[1], ft_strlen(&entry[1]) - 1);
	free(entry);
	return (new);
}

int handle_quotes(char *entry)
{
	size_t len;

	len = ft_strlen(entry);
	if (len == 1)
		return (0);
	if (entry[0] == 39 && entry[len - 1] == 39 && len > 2)
		return (1);
	if (entry[0] == 34 && entry[len - 1] == 34 && len > 2)
		return (2);
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