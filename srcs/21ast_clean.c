#include "../includes/21ast.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void clean_ast(t_ast *ast)
{
	if (ast->left)
		clean_ast(ast->left);
	if (ast->right)
		clean_ast(ast->right);
	if (ast->cmd)
		ft_str2del(ast->cmd);
	free(ast);
}