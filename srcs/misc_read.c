#include "../includes/minishell.h"

int redisplay_prompt(char *buf)
{
	if (is_only_endline(buf))
		return (1);
	else if (is_only_spaces(buf))
		return (1);
	return (0);
}