#include <stdio.h>
#include <math.h>
#include "eval/eval.h"
#include "eval/hashmap.h"
#include "eval/object.h"
#include "parser/ast_parser/ast.h"

obj*
eval_ast (hashmap *heap, ast_node *head)
{
	if (!head) return NULL;
	/* TODO maybe dont make heap in this function */
	if (!heap) {
		printf("Error: heap uninitiated\n");
		return NULL;
	}

	obj *op1 = eval_ast(heap, head->op1);
	obj *op2 = eval_ast(heap, head->op2);
	obj *res = (obj*) malloc(sizeof(obj));

	if (head->type == AST_NUM) {
		res->type = OBJ_NUM;
		res->num = head->num;

	} else if (head->type == AST_IDENTIFIER) {
		res->type = OBJ_IDENIFIER;
		res->str = (char*) calloc(strlen(head->str) + 1, sizeof(char));
		strcpy(res->str, head->str);

	} else if (head->type == AST_ASSIGNMENT) {
		if (!op1 || !op2 || op1->type != OBJ_IDENIFIER) {
			printf("Error: Invalid AST structure for \
				AST_ASSIGNMENT\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		heap = hm_set(heap, op1->str, op2);
		res->type = OBJ_NULL;
		obj_delete(op1);
		return res;

	} else if (head->type == AST_ADD) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_ADD\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = op1->num + op2->num;

	} else if (head->type == AST_SUB) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_SUB\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = op1->num - op2->num;

	} else if (head->type == AST_MUL) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MUL\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = op1->num * op2->num;

	} else if (head->type == AST_DIV) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_DIV\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = op1->num / op2->num;

	} else if (head->type == AST_NEG) {
		if (!op1) {
			printf("Error: Invalid AST structure for AST_NEG\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = -1 * op1->num;

	} else if (head->type == AST_EXP) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_EXP\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = powf(op1->num, op2->num);

	} else if (head->type == AST_MOD) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MOD\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;
		res->num = fmod(op1->num, op2->num);
	
	} else {
		printf("Error: Invalid ast_type\n");
		free(res);
		op1 = obj_delete(op1);
		op2 = obj_delete(op2);
		return NULL;
	}

	op1 = obj_delete(op1);
	op2 = obj_delete(op2);

	return res;
}
