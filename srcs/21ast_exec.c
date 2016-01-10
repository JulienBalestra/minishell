#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>

#include "../libft/includes/libft.h"
#include "../includes/21ast.h"
#include "../includes/minishell.h"

void do_ast_exec_recurse(t_ast *ast);

void manage_pipe(t_ast *ast)
{
	int		p[2];
	pid_t	pid;
	int		status;

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		dup2(p[1], ast->stdout);
		close(p[0]);
		do_ast_exec_recurse(ast->left);
	}
	else
	{
		dup2(p[0], ast->stdin);
		close(p[1]);
		waitpid(-1, &status, 0);
		do_ast_exec_recurse(ast->right);
	}
}

void manage_write(t_ast *ast)
{
	int		fd;
	pid_t	pid;
	int		status;

	if (ast->op == 2)
		fd = open(ast->right->cmd[0], O_WRONLY | O_APPEND |O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(ast->right->cmd[0], O_WRONLY | O_TRUNC | O_CREAT,
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	pid = fork();
	if (pid == 0)
	{
		dup2(fd, ast->stdout);
		do_ast_exec_recurse(ast->left);
	}
	else
	{
		close(fd);
		waitpid(-1, &status, 0);
	}
}

void manage_read(t_ast *ast)
{
	int		fd;
	pid_t	pid;
	int		status;

	//if (ast->op == 5)
	fd = open(ast->right->cmd[0], O_RDONLY);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, ast->stdin);
		do_ast_exec_recurse(ast->left);
	}
	else
	{
		close(fd);
		waitpid(-1, &status, 0);
	}
}

void do_ast_exec_recurse(t_ast *ast)
{
	char	**ptr;

	if (ast->op == -1)
	{
		ptr = ast->cmd;
		execve(ast->cmd[0], ptr, NULL);
	}
	else if (ast->op == 1)
	{
		manage_pipe(ast);
	}
	else if (ast->op == 2 || ast->op == 3)
	{
		manage_write(ast);
	}
	else if (ast->op == 5)
	{
		manage_read(ast);
	}
}

int ast_exec(t_ast *ast)
{
	pid_t	pid;
	int		status;

	pid = 0;
	if (ast->op == 1)
		pid = fork();

	if (pid == 0)
	{
		do_ast_exec_recurse(ast);
		return (0);
	}
	else
	{
		waitpid(-1, &status, 0);
		return (1);
	}
}

