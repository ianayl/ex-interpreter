#ifndef AST_PARSER_H
#define AST_PARSER_H

/* Parser (into abstract syntax trees) -- header file */

#include "lexer/tokens.h"
#include "parser/ast_parser/ast.h"

/**
 * Check the type of the next lookup-th token -- This is the k lookup in LL(k)
 * 
 * @param type expected type of the lookup-th token
 * @param lookup the nth token to lookup
 */
int expect(tk_type type, int lookup);

/**
 * Main parsing function: produces an AST from a token list head
 *
 * @param head the token list to parse -- LIST WILL BE CONSUMED
 * @param expect_indent 1 if expecting indent on next line parsed, 0 otherwise
 */
ast_node* parse_root(token *head, int *expect_indent);

/**
 * Parse an "expr" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 *
 * @param expect_indent 1 if expecting indent on next line parsed, 0 otherwise
 */
ast_node* parse_expr(int *expect_indent);

/**
 * Parse an "assign" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_assign();

/**
 * Parse an "param" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_param();

/**
 * Parse an "param'" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_paramp();

/**
 * Parse an "add" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_add();

/**
 * Parse an "add'" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_addp();

/**
 * Parse an "mul" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_mul();

/**
 * Parse an "mulp'" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_mulp();

/**
 * Parse an "exp'" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_exp();

/**
 * Parse an "exp'" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_expp();

/**
 * Parse an "term" derivation from the tokenlist, returns null if failed
 *
 * See current_grammar.md for more details
 */
ast_node* parse_term();

#endif
