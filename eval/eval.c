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
		res->type = OBJ_IDENTIFIER;
		res->identifier = (char*) calloc(strlen(head->str) + 1,
						 sizeof(char));
		strcpy(res->identifier, head->str);

	} else if (head->type == AST_ASSIGNMENT) {
		if (!op1 || !op2 || op1->type != OBJ_IDENTIFIER) {
			printf("Error: Invalid AST structure for \
				AST_ASSIGNMENT\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}

		/* 
		 * If wanted node is an identifier give back a copy of the
		 * referenced value; basically passing by value
		 */
		obj *copy;
		if (op2->type == OBJ_IDENTIFIER) {
			/* TODO this is scuffed pls make less scuffed */
			copy = (obj*) malloc(sizeof(obj));
			obj *orig = hm_get(heap, op1->identifier);
			copy->type = orig->type;
			copy->identifier = orig->identifier;
			copy->num = orig->num;
		} else copy = op2;

		heap = hm_set(heap, op1->identifier, copy);
		res->type = OBJ_NUM;
		res->num = copy->num;
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

		float op1_num, op2_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;
		if (op2->type == OBJ_IDENTIFIER) {
			op2_num = hm_get(heap, op2->identifier)->num;
		} else op2_num = op2->num;

		printf("OP1 RESULT: %f  OP2 RESULT: %f\n", op1_num, op2_num);

		res->num = op1_num + op2_num;

	} else if (head->type == AST_SUB) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_SUB\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;

		float op1_num, op2_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;
		if (op2->type == OBJ_IDENTIFIER) {
			op2_num = hm_get(heap, op2->identifier)->num;
		} else op2_num = op2->num;

		res->num = op1_num - op2_num;

	} else if (head->type == AST_MUL) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MUL\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;

		float op1_num, op2_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;
		if (op2->type == OBJ_IDENTIFIER) {
			op2_num = hm_get(heap, op2->identifier)->num;
		} else op2_num = op2->num;

		res->num = op1_num * op2_num;

	} else if (head->type == AST_DIV) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_DIV\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;

		float op1_num, op2_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;
		if (op2->type == OBJ_IDENTIFIER) {
			op2_num = hm_get(heap, op2->identifier)->num;
		} else op2_num = op2->num;

		res->num = op1_num / op2_num;

	} else if (head->type == AST_NEG) {
		if (!op1) {
			printf("Error: Invalid AST structure for AST_NEG\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;

		float op1_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;

		res->num = -1 * op1_num;

	} else if (head->type == AST_EXP) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_EXP\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;

		float op1_num, op2_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;
		if (op2->type == OBJ_IDENTIFIER) {
			op2_num = hm_get(heap, op2->identifier)->num;
		} else op2_num = op2->num;

		res->num = powf(op1_num, op2_num);

	} else if (head->type == AST_MOD) {
		if (!op1 || !op2) {
			printf("Error: Invalid AST structure for AST_MOD\n");
			free(res);
			op1 = obj_delete(op1);
			op2 = obj_delete(op2);
			return NULL;
		}
		res->type = OBJ_NUM;

		float op1_num, op2_num;
		if (op1->type == OBJ_IDENTIFIER) {
			op1_num = hm_get(heap, op1->identifier)->num;
		} else op1_num = op1->num;
		if (op2->type == OBJ_IDENTIFIER) {
			op2_num = hm_get(heap, op2->identifier)->num;
		} else op2_num = op2->num;

		res->num = fmod(op1_num, op2_num);
	
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
