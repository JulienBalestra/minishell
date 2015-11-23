#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "../includes/minishell.h"

void remove_link(t_env *link)
{
	if (link)
	{
		free(link->name);
		link->name = NULL;
		free(link->value);
		link->value = NULL;
		free(link);
	}
}

void delete_list(t_env **env)
{
	t_env *current;

	while (*env)
	{
		current = (*env)->next;
		remove_link(*env);
		*env = current;
	}
}

void clean_program(t_sh *shell)
{
	delete_list(&(shell->env));
	ft_str2del(shell->last_environ);
	free(shell->env);
	free(shell->prompt);
	if (shell->mock)
		clean_program(shell->mock);
	ft_str2del(shell->last_command);
	if (shell->buf)
		free(shell->buf);
	free(shell);
}