#ifndef EVAL_H
#define EVAL_H

#include "parser/ast_parser/ast.h"

typedef struct object {
	float num;
} obj;

obj* eval_ast (ast_node *head);

#endif
