#ifndef EVAL_H
#define EVAL_H

#include "parser/ast_parser/ast.h"
#include "eval/object.h"
#include "eval/hashmap.h"

obj* eval_ast (hashmap *heap, ast_node *head);

#endif
