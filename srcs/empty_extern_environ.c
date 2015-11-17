
#include <unistd.h>
#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_env *manage_empty_environ(void)
{
	char *buf_pwd;
	char *string;
	t_env *env;

	env = NULL;
	if ((buf_pwd = (char *) malloc(sizeof(char) * 2048)))
	{
		string = ft_strjoin("PWD=", getcwd(buf_pwd, 2048));
		env = create_env_link(env, string);
		free(buf_pwd);
		free(string);
	}
	return (env);
}