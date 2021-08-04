#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum AST_type {
	AST_NULL,
	AST_ASTLIST,
	AST_PARAMLIST,
	AST_EPSILON,
	AST_NUM,
	AST_IDENTIFIER,
	AST_ASSIGNMENT,
	AST_ADD,
	AST_SUB,
	AST_MUL,
	AST_DIV,
	AST_NEG,
	AST_EXP,
	AST_MOD,
	AST_FN,
	AST_RETURN
} ast_type;

typedef struct AST_node {
	ast_type type;
	struct AST_node *op1;
	union {
		struct AST_node *op2;
		struct AST_node *next;
	};
	union {
		float num;
		char* str;
		struct AST_node* params;
		struct AST_node* ast;
	};
} ast_node;

ast_node* ast_new(ast_type type, ast_node *op1, ast_node *op2, float num, 
		  char* str);

void ast_print_node(ast_node *node);

void ast_print_preorder(ast_node *head, int lvl);

ast_node* ast_free(ast_node *head);

#endif
