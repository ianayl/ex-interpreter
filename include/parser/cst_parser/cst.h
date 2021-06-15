#ifndef CST_H
#define CST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum CST_type {
	CST_NULL,
	CST_EPSILON,
	CST_ADD,
	CST_ADDP,
	CST_MUL,
	CST_MULP,
	CST_TERM,
	CST_NUM,
} cst_type;

typedef struct CST_node {
	cst_type type;
	struct CST_node *op1;
	struct CST_node *op2;
	int val;
} cst_node;

cst_node* cst_new (cst_type type, cst_node *op1, cst_node *op2, int val);

void cst_print_node (cst_node* node);

void cst_print_preorder (cst_node* head, int lvl);

#endif
