#ifndef CST_PARSER_H
#define CST_PARSER_H

#include "lexer/tokens.h"
#include "parser/ast_parser/ast.h"

token* tokens = NULL;

int expect(tk_type type);

ast_node* parse_root (token *head);
ast_node* parse_add ();
ast_node* parse_addp ();
ast_node* parse_mul ();
ast_node* parse_mulp ();
ast_node* parse_term ();

#endif
