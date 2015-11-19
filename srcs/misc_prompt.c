#include "minishell.h"
#include "libft.h"
#include <unistd.h>

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void display_prompt(t_sh *shell)
{
	write(1, shell->prompt, shell->len_prompt);
}

void display_command_not_found(char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void display_not_such(char *who, char *where)
{
	ft_putstr_fd(who, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(where, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}