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

	if (is_only_env(command))
		display_environ(shell->last_environ, 1);
	else if ((benv = build_builtin_env(command)))
	{
		if (is_benv_errors(benv) || is_benv_do_nothing(benv))
			;
		else if (benv->ignore == 1 && benv->cmd == 0 && benv->set == 1)
			display_only_setenv(command, benv->null ? 0 : 1);
		else if (benv->ignore == 1 && benv->cmd == 1)
			run_under_new_environ(command, shell);
		else if (benv->cmd == 1)
			run_under_alter_environ(command, shell);
		else if (benv->cmd == 0)
			alter_environ_and_display(command, shell, benv->null ? 0 : 1);

		free(benv);
	}
}