#include "libft.h"
#include "../libft/includes/libft.h"

void display_cd_invalid_option(char *opt)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(opt, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("cd: usage: cd [-L OR -P] [dir]\n", 2);
}