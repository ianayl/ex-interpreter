#ifndef AST_PARSER_H
#define AST_PARSER_H

#include "lexer/tokens.h"
#include "parser/ast_parser/ast.h"

int expect(tk_type type, int lookup);

ast_node* parse_root(token *head, int *expect_indent);
ast_node* parse_expr(int *expect_indent);
ast_node* parse_assign();
ast_node* parse_param();
ast_node* parse_paramp();
ast_node* parse_add();
ast_node* parse_addp();
ast_node* parse_mul();
ast_node* parse_mulp();
ast_node* parse_exp();
ast_node* parse_expp();
ast_node* parse_term();

#endif
