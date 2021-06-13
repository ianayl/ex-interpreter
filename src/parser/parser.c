#include "tokens.h"
#include <stdlib.h>

/* 
 * Current Grammar:
 *
 * Start -> Add
 * Add -> Mul '+' Add
 * Add -> Mul
 * Mul -> Term '*' Mul
 * Mul -> Term
 * Term -> Num
 * Term -> '-' Term
 * Term -> '(' Add ')'
 *
 * Left Refactored:
 *
 * Start -> Add
 *
 * Add -> Mul Add'
 * Add' -> '+' Add
 * Add' -> Epsilon
 *
 * Mul -> Term Mul'
 * Mul' -> '*' Mul
 * Mul' -> Epsilon
 *
 * Term -> Num
 * Term -> '-' Term
 * Term -> '(' Add ')'
 *
 */

token* tokens = NULL;

typedef enum CST_type {
	CST_NULL,
	CST_EPSILON,
	CST_ADD,
	CST_ADDP,
	CST_MUL,
	CST_MULP,
	CST_TERM,
	CST_NUM,
} cst_type;

typedef struct CST_node {
	cst_type type;
	struct CST_node *op1;
	struct CST_node *op2;
	int val;
} cst_node;

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

int 
expect (tk_type type)
{
	if (tokens->next && tokens->next->type == type)
		return 1;
	return 0;
}

cst_node* parse_root (token *head);
cst_node* parse_add ();
cst_node* parse_addp ();
cst_node* parse_mul ();
cst_node* parse_mulp ();
cst_node* parse_term ();

cst_node* 
parse_root (token *head)
{
	tokens = head;
	cst_node *res = parse_add();
	if (!res) {
		/* TODO raise error: Invalid parse */
	} else if (tokens) {
		/* TODO raise error: Unfinished grammar */
	}
	return res;
}

cst_node*
parse_add ()
{
	/* Add -> Mul Add' */
	cst_node *mul = parse_mul();
	if (!mul)
		/* TODO raise error */
		return NULL;
	cst_node *addp = parse_addp();
	if (!addp) {
		/* TODO FREE mul WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		return NULL;
	}
	return cst_new(CST_ADD, mul, addp, 0);
}

cst_node*
parse_addp ()
{
	/* Add' -> '+' Add */
	cst_node *res = cst_new(CST_ADDP, NULL, NULL, 0);
	if (expect(OP_ADD)) {
		tokens = tk_pop_ll(tokens);
		res->op1 = parse_add(); 
		if (!res->op1)
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
	} else
		res->op1 = cst_new(CST_EPSILON, NULL, NULL, 0);
	return res;
}

cst_node*
parse_mul ()
{
	/* Mul -> Term Mul' */
	cst_node* term = parse_term();
	if (!term)
		/* TODO raise error */
		return NULL;
	cst_node* mulp = parse_mulp();
	if (!mulp) {
		/* TODO FREE term WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		return NULL;
	}
	return cst_new(CST_MUL, term, mulp, 0);
}

cst_node*
parse_mulp ()
{
	cst_node* res = cst_new(CST_MULP, NULL, NULL, 0);
	if (expect(OP_MUL)) {
		/* Mul' -> '*' Mul */
		tokens = tk_pop_ll(tokens);
		res->op1 = parse_mul();
		if (!res->op1) {
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}
	} else
		/* Mul' -> Epsilon */
		res->op1 = cst_new(CST_EPSILON, NULL, NULL, 0);]
	return res;
}

cst_node*
parse_term ()
{
	/* Term -> Num */
	if (expect(INTEGER)) {
		cst_node* num = cst_new(CST_NUM, NULL, NULL, tokens->num);
		tokens = tk_pop_ll(tokens);
		return cst_new(CST_TERM, num, NULL, 0);
	}
	/* TODO raise error */
	return NULL;
}

int
main ()
{
	token* list = tk_new(INTEGER, 4);
	tk_append_ll(list, tk_new(OP_ADD, 0));
	tk_append_ll(list, tk_new(INTEGER, 2));
	tk_append_ll(list, tk_new(OP_MUL, 0));
	tk_append_ll(list, tk_new(INTEGER, 0));

	// token* src = tk_ll_to_arr(list);
	// int src_len = tk_len_ll(list);

	// parse_root(src, src_len);
	
	tk_print_ll(list);

	parse_root(list);

	tk_delete_ll(list);

	// tk_print_arr(src, src_len);
	// free(src);
}
