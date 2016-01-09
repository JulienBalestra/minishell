#include "../libft/includes/libft.h"
#include "../includes/21ast.h"
#include "minishell.h"

int main(void)
{
	t_ast *ast;
	char one[] = "ls -l | cat -e | sort";
	ast = build_ast(ft_strdup(one));
	ast_read(ast);
	clean_ast(ast);
	return (1);
}