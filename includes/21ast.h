//
// Created by jynlee on 03/01/16.
//

#ifndef AST_MAIN_H
#define AST_MAIN_H

typedef struct	s_ast
{
	int 			op; // "|"
	char 			**cmd; // { "cat", "-e", "NULL"}
	struct s_ast	*left;
	struct s_ast	*right;

}					t_ast;

t_ast *build_ast(char *input);
void clean_ast(t_ast *ast);
void ast_read(t_ast *ast);


#endif // AST_MAIN_H
