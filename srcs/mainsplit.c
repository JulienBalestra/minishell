#include <string.h>
#include <stdio.h>

char		**ft_strsplit(char const *s, char c);



int main(int ac, char **av)
{
	char **split;
	int i = 0;

	split = NULL;
	if (ac != 2)
		return (1);
	else
	{
		split = ft_strsplit(av[1], ' ');
		while (split[i])
		{
			puts(split[i]);
			i++;
		}
	}
	return (0);
}

