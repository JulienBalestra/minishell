#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <signal.h>

#include "../libft/includes/libft.h"
#include "../includes/21ast.h"
#include "../includes/minishell.h"

void do_ast_exec_recurse(t_ast *ast)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	**ptr;

	if (ast->op == -1)
	{
		ptr = ast->cmd;
		execve(ast->cmd[0], ptr, NULL);
	}
	else
	{
		pipe(p);
		pid = fork();
		if (pid == 0)
		{
			dup2(p[1], 1);
			close(p[0]);
			ast_exec(ast->left);
		}
		else
		{
			dup2(p[0], 0);
			close(p[1]);
			waitpid(-1, &status, 0);
			ast_exec(ast->right);
		}
	}
}

int ast_exec(t_ast *ast)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		do_ast_exec_recurse(ast);
		//kill(getpid(), 15);
		return (0);
	}
	else
	{
		waitpid(-1, &status, 0);
		return (1);
	}
}

