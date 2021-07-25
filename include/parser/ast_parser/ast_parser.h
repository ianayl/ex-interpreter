#ifndef AST_PARSER_H
#define AST_PARSER_H

#include "lexer/tokens.h"
#include "parser/ast_parser/ast.h"

int expect(tk_type type);

ast_node* parse_root(token *head);
ast_node* parse_expr();
ast_node* parse_assign();
ast_node* parse_assignp();
ast_node* parse_add();
ast_node* parse_addp();
ast_node* parse_mul();
ast_node* parse_mulp();
ast_node* parse_exp();
ast_node* parse_expp();
ast_node* parse_term();

#endif
