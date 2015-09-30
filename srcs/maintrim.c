#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *ft_str_trimed(char *s, char c);

int main(int ac, char **av)
{
	char *trim;

	trim = NULL;
	if (ac != 2)
		return (1);
	else
	{
		puts(av[1]);
		trim = ft_str_trimed(av[1], 't');
		puts(trim);
		free(trim);		
	}
	return (0);
}

