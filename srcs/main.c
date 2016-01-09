#include "../libft/includes/libft.h"
#include "../includes/21ast.h"
#include "minishell.h"

int main(void)
{
	t_ast *ast;
	//char one[] = "ls -lr | cat -e | sort";
	char one[] = "/bin/ls -lr | /bin/cat -e | /usr/bin/sort | /usr/bin/rev | /usr/bin/rev";
	ast = build_ast(ft_strdup(one));
	ast_read(ast);
	ft_putstr("\n");
	if (ast_exec(ast))
	{
		//do_something;
	}
	clean_ast(ast);
	return (1);
}