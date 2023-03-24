#ifndef CST_PARSER_H
#define CST_PARSER_H

/* 
 * DEPRECATED -- USE AST_PARSER INSTEAD
 */

#include "lexer/tokens.h"
#include "parser/cst_parser/cst.h"

token* tokens = NULL;

int expect(tk_type type);

cst_node* parse_root (token *head);
cst_node* parse_add ();
cst_node* parse_addp ();
cst_node* parse_mul ();
cst_node* parse_mulp ();
cst_node* parse_term ();

#endif
