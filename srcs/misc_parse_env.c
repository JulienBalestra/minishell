#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int is_only_env(char **command)
{
	if (tab_len(command) == 1)
		return (1);
	return (0);
}

int is_null_arg(char *arg)
{
	if (ft_strcmp("-0", arg) == 0 || ft_strcmp("--null", arg) == 0)
		return (1);
	return (0);
}

int is_ignore_arg(char *arg)
{
	if (ft_strcmp(arg, "-i") == 0 ||
		ft_strcmp(arg, "--ignore-environment") == 0)
		return (1);
	return (0);
}

int is_setenv(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
