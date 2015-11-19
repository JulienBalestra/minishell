#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

void display_environ(char **to_display, int end_line)
{
	if (!to_display)
		return;
	while (*to_display)
	{
		ft_putstr(*to_display);
		if (end_line == 1)
			ft_putchar('\n');
		to_display++;
	}
}

void display_only_setenv(char **command, int end_line)
{
	while (command && *command)
	{
		if (is_setenv(*command))
		{
			ft_putstr(*command);
			if (end_line)
				ft_putchar('\n');
			else
				ft_putchar('\x00');
		}
		command++;
	}
}