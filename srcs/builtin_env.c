#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_be *build_builtin_env(char **command)
{
	t_be *benv;

	if ((benv = (t_be *) malloc(sizeof(t_be))))
	{
		benv->ignore = have_ignore(command);
		benv->unet = have_unsets(command);
		benv->set = have_setenv(command);
		benv->null = have_null(command);
		benv->cmd = have_command(command);
	}
	return (benv);
}

void builtin_env(char **command, t_sh *shell)
{
	t_be *benv;
	(void) shell;

	if (is_only_env(command))
		display_environ(shell->last_environ, 1);
	else if ((benv = build_builtin_env(command)))
	{
		if (is_builtin_env_errors(benv) == 1)
			;
		else if (benv->ignore == 1 && benv->cmd == 0 && benv->set == 0)
		{
			display_environ(NULL, 0); // env -i do nothing
		}
		else if (benv->ignore == 1 && benv->cmd == 0 && benv->set == 1)
		{
			display_only_setenv(command, benv->null ? 0 : 1);
		}
		free(benv);
	}
}