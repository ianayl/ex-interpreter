#include <stdio.h>
#include <math.h>
#include "eval/eval.h"

obj*
eval_ast (ast_node *head)
{
	if (!head) return NULL;

	obj *op1 = eval_ast(head->op1);
	obj *op2 = eval_ast(head->op2);
	obj *res = (obj*) malloc(sizeof(obj));

	if (head->type == AST_NUM)
		res->num = head->num;
	else if (head->type == AST_ADD) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_ADD\n");
			free(res);
			if (op1) free(op1);
			if (op2) free(op2);
			return NULL;
		}
		res->num = op1->num + op2->num;
	} else if (head->type == AST_SUB) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_SUB\n");
			free(res);
			if (op1) free(op1);
			if (op2) free(op2);
			return NULL;
		}
		res->num = op1->num - op2->num;
	} else if (head->type == AST_MUL) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MUL\n");
			free(res);
			if (op1) free(op1);
			if (op2) free(op2);
			return NULL;
		}
		res->num = op1->num * op2->num;
	} else if (head->type == AST_DIV) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_DIV\n");
			free(res);
			if (op1) free(op1);
			if (op2) free(op2);
			return NULL;
		}
		res->num = op1->num / op2->num;
	} else if (head->type == AST_NEG) {
		if (!op1) {
			printf("Error: Invalid AST structure for AST_NEG\n");
			free(res);
			if (op1) free(op1);
			if (op2) free(op2);
			return NULL;
		}
		res->num = -1 * op1->num;
	} else if (head->type == AST_EXP) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_EXP\n");
			free(res);
			if (op1) free(op1);
			if (op2) free(op2);
			return NULL;
		}
		res->num = powf(op1->num, op2->num);

	} else if (head->type == AST_MOD) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MOD\n");
	     	free(res);
			return NULL;
		}
		res->num = fmod(op1->num, op2->num);
	
	} else {
		printf("Error: Invalid ast_type\n");
		free(res);
		if (op1) free(op1);
		if (op2) free(op2);
		return NULL;
	}

	if (op1) free(op1);
	if (op2) free(op2);

	return res;
}
