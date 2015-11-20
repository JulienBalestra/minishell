#include <stdlib.h>
#include "../libft/includes/libft.h"

int tab_len(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			i++;
		}
	}
	return (i);
}

void tab_free(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void replace_null(char **command, int original)
{
	int i;
	int j;
	int b;

	i = 0;
	if (original != tab_len(command))
	{
		while (i < original + 1)
		{
			if (command[i] == NULL)
			{
				b = i;
				j = i + 1;
				while (j < original + 1)
				{
					command[i] = command[j];
					i++;
					j++;
				}
				i = b;
			}
			i++;
		}
	}
}

char **tab_dup(char **tab)
{
	char **dup;
	int i;
	size_t len;

	len = (size_t) tab_len(tab);
	i = 0;
	if ((dup = (char **)malloc(sizeof(char *) * (len + 1))))
	{
		while (tab[i])
		{
			dup[i] = ft_strdup(tab[i]);
			i++;
		}
		dup[i] = NULL;
	}
	return (dup);
}