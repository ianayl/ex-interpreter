#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum AST_type {
	AST_NULL,
	AST_EPSILON,
	AST_NUM,
	AST_ADD,
	AST_SUB,
	AST_MUL,
	AST_DIV,
	AST_NEG,
	AST_EXP,
	AST_MOD,
} ast_type;

typedef struct AST_node {
	ast_type type;
	struct AST_node *op1;
	struct AST_node *op2;
	float val;
} ast_node;

ast_node* ast_new (ast_type type, ast_node *op1, ast_node *op2, float val);

void ast_print_node (ast_node *node);

void ast_print_preorder (ast_node *head, int lvl);

ast_node* ast_free (ast_node *head);

#endif
