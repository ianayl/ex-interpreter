#ifndef EVAL_H
#define EVAL_H

#include "parser/ast_parser/ast.h"

/* TODO reconsider putting objects in eval.h as project expands */
typedef struct object {
	float num;
} obj;

obj* eval_ast (ast_node *head);

#endif
