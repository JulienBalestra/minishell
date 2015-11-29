#include "../libft/includes/libft.h"

int is_physical(char *str)
{
	if (ft_strcmp("-P", str) == 0)
		return (1);
	return (0);
}

int is_logical(char *str)
{
	if (ft_strcmp("-L", str) == 0)
		return (1);
	return (0);
}

int is_minus(char *str)
{
	if (ft_strcmp("-", str) == 0)
		return (1);
	return (0);
}
