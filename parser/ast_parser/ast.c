#include "parser/ast_parser/ast.h"

ast_node* 
ast_new(ast_type type, ast_node *op1, ast_node *op2, float num, char* str)
{
	ast_node *res = (ast_node*) malloc(sizeof(ast_node));
	res->type = type;
	res->op1 = op1;
	res->op2 = op2;
	if (type == AST_IDENTIFIER) {
		/* TODO I don't actually know if the calloc is needed here */
		res->str = (char*) calloc(strlen(str) + 1, sizeof(char));
		strcpy(res->str, str);
	} else res->num = num;
	return res;
}

void
ast_print_node(ast_node* node)
{
	if (!node) return;

	if (node->type == AST_NULL)
		printf("AST: Null\n");
	else if (node->type == AST_NUM)
		printf("AST: Num: %f\n", node->num);
	else if (node->type == AST_IDENTIFIER)
		printf("AST: Identifier: %s\n", node->str);
	else if (node->type == AST_ASSIGNMENT)
		printf("AST: Assignment =\n");
	else if (node->type == AST_ADD)
		printf("AST: Add +\n");
	else if (node->type == AST_SUB)
		printf("AST: Sub -\n");
	else if (node->type == AST_MUL)
		printf("AST: Mul *\n");
	else if (node->type == AST_DIV) 
		printf("AST: Div /\n");
	else if (node->type == AST_NEG) 
		printf("AST: Neg -\n");
	else if (node->type == AST_EXP) 
		printf("AST: Exp ^\n");
	else if (node->type == AST_MOD) 
		printf("AST: Mod %%\n");
	else if (node->type == AST_EPSILON)
		printf("AST: Epsilon (??? how)\n");
	else
		printf("ERROR: ast_print_node - Unknown type\n");
}

void
ast_print_preorder(ast_node *head, int lvl)
{
	if (!head) return;

	for (int i = 0; i < lvl; i++) printf("    ");
	ast_print_node(head);

	ast_print_preorder(head->op1, lvl + 1);
	ast_print_preorder(head->op2, lvl + 1);
}

ast_node*
ast_free(ast_node *head)
{
	if (!head) return NULL;
	/* Epsilon is usually a special node; don't delete epsilon */
	if (head->type == AST_EPSILON) return NULL;

	ast_free(head->op1);
	ast_free(head->op2);
	if (head->type == AST_IDENTIFIER) free(head->str);
	free(head);

	return NULL;
}
