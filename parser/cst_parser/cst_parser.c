#include "parser/cst_parser/cst_parser.h"
#include "parser/cst_parser/cst.h"

int 
expect (tk_type type)
{
	/* if (tokens->next && tokens->next->type == type) return 1; */
	if (tokens && tokens->type == type) return 1;
	return 0;
}

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
	/* <Add> ::= <Mul> <Add'> */
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
	/* <Add'> ::= '+' <Add> */
	cst_node *res = cst_new(CST_ADDP, NULL, NULL, 0);
	if (expect(TOK_ADD)) {
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
	/* <Mul> ::= <Term> <Mul'> */
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
	if (expect(TOK_MUL)) {
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
	/* <Term> ::= <Num> */
	if (expect(TOK_NUM)) {
		printf("Info: Num found\n");
		cst_node* num = cst_new(CST_NUM, NULL, NULL, tokens->num);
		tokens = tk_pop_ll(tokens);
		return cst_new(CST_TERM, num, NULL, 0);
	/* Term ::= '(' <Add> ')' */
	} else if (expect(TOK_LPAREN)) {
		printf("Info: '(' found\n");
		tokens = tk_pop_ll(tokens);
		cst_node* add = parse_add();
		if (!add) {
			printf("Error: parse_add returned null\n");
			return NULL;
		}
		if (!expect(TOK_RPAREN)) {
			printf("Error: Expected ')'\n");
			return NULL;
		}
		tokens = tk_pop_ll(tokens);
		return cst_new(CST_TERM, add, NULL, 0);
	}
	/* TODO raise error */
	printf("Error: Expected Num not found\n");
	return NULL;
}

int
main ()
{
	token* list = tk_new(TOK_LPAREN, 0);
	tk_append_ll(list, tk_new(TOK_NUM, 1));
	tk_append_ll(list, tk_new(TOK_ADD, 0));
	tk_append_ll(list, tk_new(TOK_NUM, 2));
	tk_append_ll(list, tk_new(TOK_RPAREN, 0));
	tk_append_ll(list, tk_new(TOK_ADD, 0));
	tk_append_ll(list, tk_new(TOK_LPAREN, 0));
	tk_append_ll(list, tk_new(TOK_NUM, 3));
	tk_append_ll(list, tk_new(TOK_ADD, 0));
	tk_append_ll(list, tk_new(TOK_NUM, 4));
	tk_append_ll(list, tk_new(TOK_RPAREN, 0));

	// token* src = tk_ll_to_arr(list);
	// int src_len = tk_len_ll(list);

	// parse_root(src, src_len);
	
	// tk_print_ll(list);

	cst_node* test = parse_root(list);
	cst_print_preorder(test, 0);
	// cst_print_node(test);

	// tk_delete_ll(list);

	// tk_print_arr(src, src_len);
	// free(src);
}
