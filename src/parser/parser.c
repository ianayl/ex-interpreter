#include "tokens.h"
#include <stdlib.h>
#include <stdio.h>

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

void
cst_print_node (cst_node* node)
{
	if (!node) return;

	if (node->type == CST_NULL)
		printf("CST: Null\n");
	else if (node->type == CST_EPSILON)
		printf("CST: Epsilon\n");
	else if (node->type == CST_ADD)
		printf("CST: Add\n");
	else if (node->type == CST_ADDP)
		printf("CST: Add'\n");
	else if (node->type == CST_MUL)
		printf("CST: Mul\n");
	else if (node->type == CST_MULP) 
		printf("CST: Mul'\n");
	else if (node->type == CST_TERM) 
		printf("CST: Term\n");
	else if (node->type ==  CST_NUM)
		printf("CST: Num: %d\n", node->val);
	else
		printf("cst_print_node: ERROR - Unknown type\n");
}

void
cst_print_preorder (cst_node* head)
{
	if (!head) return;
	cst_print_node(head);
	cst_print_preorder(head->op1);
	cst_print_preorder(head->op2);
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
	tk_print_ll(tokens);
	cst_node *res = parse_add();
	if (!res) {
		/* TODO raise error: Invalid parse */
		printf("Error: tree is null\n");
	} 
	if (tokens) {
		/* TODO raise error: Unfinished grammar */
		printf("Error: tokens left. LEFTOVER TOKENS:\n");
		tk_print_ll(tokens);
	}
	return res;
}

cst_node*
parse_add ()
{
	/* Add -> Mul Add' */
	cst_node *mul = parse_mul();
	if (!mul) {
		/* TODO raise error */
		printf("Error: parse_mul returned null\n");
		return NULL;
	}
	cst_node *addp = parse_addp();
	if (!addp) {
		/* TODO FREE mul WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_addp returned null\n");
		return NULL;
	}
	return cst_new(CST_ADD, mul, addp, 0);
}

cst_node*
parse_addp ()
{
	/* Add' -> '+' Add */
	cst_node *res = cst_new(CST_ADDP, NULL, NULL, 0);
	// if (expect(OP_ADD)) {
	if (tokens && tokens->type == OP_ADD) {
		printf("Info: Expected '+' found\n");
		tokens = tk_pop_ll(tokens);
		res->op1 = parse_add(); 
		if (!res->op1) {
			printf("Error: parse_add returned null\n");
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}
	} else {
		printf("Info: '*' not found, reducing to epsilon\n");
		res->op1 = cst_new(CST_EPSILON, NULL, NULL, 0);
	}
	return res;
}

cst_node*
parse_mul ()
{
	/* Mul -> Term Mul' */
	cst_node* term = parse_term();
	if (!term) {
		/* TODO raise error */
		printf("Error: parse_term returned null\n");
		return NULL;
	}
	cst_node* mulp = parse_mulp();
	if (!mulp) {
		/* TODO FREE term WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_mulp returned null\n");
		return NULL;
	}
	return cst_new(CST_MUL, term, mulp, 0);
}

cst_node*
parse_mulp ()
{
	cst_node* res = cst_new(CST_MULP, NULL, NULL, 0);
	// if (expect(OP_MUL)) {
	if (tokens && tokens->type == OP_MUL) {
		/* Mul' -> '*' Mul */
		printf("Info: Expected '*' found\n");
		tokens = tk_pop_ll(tokens);
		res->op1 = parse_mul();
		if (!res->op1) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_mul returned null\n");
			return NULL;
		}
	} else {
		/* Mul' -> Epsilon */
		printf("Info: '*' not found, reducing to epsilon\n");
		res->op1 = cst_new(CST_EPSILON, NULL, NULL, 0);
	}
	return res;
}

cst_node*
parse_term ()
{
	/* Term -> Num */
	// if (expect(INTEGER)) {
	if (tokens && tokens->type == INTEGER) {
		printf("Info: Num found\n");
		cst_node* num = cst_new(CST_NUM, NULL, NULL, tokens->num);
		tokens = tk_pop_ll(tokens);
		return cst_new(CST_TERM, num, NULL, 0);
	}
	/* TODO raise error */
	printf("Error: Expected Num not found\n");
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
	
	// tk_print_ll(list);

	cst_node* test = parse_root(list);
	cst_print_preorder(test);
	// cst_print_node(test);

	// tk_delete_ll(list);

	// tk_print_arr(src, src_len);
	// free(src);
}
