#include <stdlib.h>
#include "../libft/includes/libft.h"

void replace_null(char **command, size_t original)
{
	size_t i;
	size_t j;
	size_t b;

	i = 0;
	if (original != ft_str2len(command))
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