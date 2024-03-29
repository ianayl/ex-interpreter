#include "parser/cst_parser/cst.h"

/*
 * THIS FILE IS DEPRECATED
 *
 * It is inefficient to convert to a CST and then convert the CST into an AST,
 * or vice versa, although less inefficient, evaluate a CST instead of an AST.
 * For efficiency's sake, I will be parsing to an AST from now on.
 */

cst_node* 
cst_new (cst_type type, cst_node *op1, cst_node *op2, int val)
{
	cst_node *res = (cst_node*) malloc(sizeof(cst_node));
	res->type = type;
	res->op1 = op1;
	res->op2 = op2;
	res->val = val;
	return res;
}

void
cst_print_node (cst_node* node)
{
	if (!node) return;

	if (node->type == CST_NULL)
		printf("CST: Null\n");
	else if (node->type == CST_EPSILON)
		printf("CST: Epsilon\n");
	else if (node->type == CST_ADD)
		printf("CST: Add\n");
	else if (node->type == CST_ADDP)
		printf("CST: Add'\n");
	else if (node->type == CST_MUL)
		printf("CST: Mul\n");
	else if (node->type == CST_MULP) 
		printf("CST: Mul'\n");
	else if (node->type == CST_TERM) 
		printf("CST: Term\n");
	else if (node->type ==  CST_NUM)
		printf("CST: Num: %d\n", node->val);
	else
		printf("cst_print_node: ERROR - Unknown type\n");
}

void
cst_print_preorder (cst_node* head, int lvl)
{
	if (!head) return;
	for (int i = 0; i < lvl; i++) printf("    ");
	cst_print_node(head);
	cst_print_preorder(head->op1, lvl + 1);
	cst_print_preorder(head->op2, lvl + 1);
}
