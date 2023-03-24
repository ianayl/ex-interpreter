#ifndef EVAL_H
#define EVAL_H

/* Tree-walk evaluator -- header file */

#include "parser/ast_parser/ast.h"
#include "eval/object.h"
#include "eval/hashmap.h"

/**
 * Evaluate (tree-walk) an AST (or a subtree of an AST)
 *
 * @param heap the hashmap associated with the current activation record / scope
 * @param head the AST to evaluate
 * @return the resulting value of the AST (as an object)
 */
obj* eval_ast (hashmap *heap, ast_node *head);
// TODO: heap is a bad name for this, clean this up in the future

#endif
