#ifndef AST_H
#define AST_H

typedef struct	s_ast
{
	int 			op;
	int 			stdin;
	int 			stdout;
	char 			**cmd;
	struct s_ast	*left;
	struct s_ast	*right;

}					t_ast;

t_ast *build_ast(char *input);
void clean_ast(t_ast *ast);
void ast_read(t_ast *ast);
int ast_exec(t_ast *ast);

#endif // AST_H
