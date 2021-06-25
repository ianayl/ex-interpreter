#include <stdio.h>
#include "eval/eval.h"

obj*
eval_ast (ast_node *head)
{
	if (!head) return NULL;

	obj *op1 = eval_ast(head->op1);
	obj *op2 = eval_ast(head->op2);
	obj *res = (obj*) malloc(sizeof(obj));

	if (head->type == AST_NUM)
		res->num = head->val;
	else if (head->type == AST_ADD) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_ADD\n");
			return NULL;
		}
		res->num = op1->num + op2->num;
	}
	else if (head->type == AST_MUL) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MUL\n");
			return NULL;
		}
		res->num = op1->num * op2->num;
	} else {
		printf("Error: Invalid ast_type\n");
		return NULL;
	}

	if (op1) free(op1);
	if (op2) free(op2);

	return res;
}
