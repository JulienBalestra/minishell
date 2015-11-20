#include <stdlib.h>
#include "../libft/includes/libft.h"

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
	if (entry[0] == 39 && entry[ft_strlen(entry) - 1] == 39)
		return (1);
	if (entry[0] == 34 && entry[ft_strlen(entry) - 1] == 34)
		return (2);
	return (0);
}

