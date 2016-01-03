#include "../libft/includes/libft.h"
#include "21ast.h"
#include "minishell.h"

int main(void)
{
	t_ast *ast;
	char one[] = "ls -l >> cat -e | sort";
	ast = build_ast(ft_strdup(one));
	ft_putstr(ast->left->left->cmd[0]);
	ft_putstr(" ");
	ft_putstr(ast->left->left->cmd[1]);
	ft_putstr(" ");
	ft_putnbr(ast->left->op);
	ft_putstr(" ");
	ft_putstr(ast->left->right->cmd[0]);
	ft_putstr(" ");
	ft_putstr(ast->left->right->cmd[1]);
	ft_putstr(" ");
	ft_putnbr(ast->op);
	ft_putstr(" ");
	ft_putstr(ast->right->cmd[0]);
	ft_putstr("\n");
	clean_ast(ast);
	return (1);
}