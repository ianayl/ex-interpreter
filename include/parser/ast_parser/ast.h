#ifndef AST_H
#define AST_H

/* Abstract syntax tree nodes -- header file */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Types that all AST's can be as */
typedef enum AST_type {
	AST_NULL,
	AST_ASTLIST, /* A list of AST's, used in e.g. function bodies */
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
		/* 
		 * Convention:
		 * - Binary operators use op2
		 * - Other operators use next (e.g. parameter lists in functions)
		 */
		struct AST_node *op2;
		struct AST_node *next;
	};
	union { /* Value of the AST node: each node can only have one value type */
		float num;
		char* str;
		struct AST_node* params; /* AST is a list of parameters */
		struct AST_node* ast; /* AST contains a sub-AST (e.g. If bool value) */
	};
} ast_node;

/**
 * Construct a new AST node
 */
ast_node* ast_new(ast_type type, ast_node *op1, ast_node *op2, float num, 
		  char* str);

/**
 * Print the current AST node
 */
void ast_print_node(ast_node *node);

/**
 * Print information about the root node before printing information about its
 * children: In other words, print level by level
 *
 * @param head pointer to the AST to print
 * @param lvl level to indent the printed output by (If you don't know what this
 *            means just use 0) 
 */
void ast_print_preorder(ast_node *head, int lvl);

/**
 * Function to clean up and free an AST
 *
 * @param head pointer to the AST to free
 * @return the new value of the pointer to the AST (usually NULL)
 */
ast_node* ast_free(ast_node *head);

#endif
