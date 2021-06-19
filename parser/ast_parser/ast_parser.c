#include "parser/ast_parser/ast_parser.h"
#include "parser/ast_parser/ast.h"

int 
expect (tk_type type)
{
	/* if (tokens->next && tokens->next->type == type) return 1; */
	if (tokens && tokens->type == type) return 1;
	return 0;
}

ast_node* 
parse_root (token *head)
{
	tokens = head;
	tk_print_ll(tokens);
	ast_node *res = parse_add();
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

ast_node*
parse_add ()
{
	/* <Add> ::= <Mul> <Add'> */
	ast_node *mul = parse_mul();
	if (!mul) {
		/* TODO raise error */
		printf("Error: parse_mul returned null\n");
		return NULL;
	}
	ast_node *addp = parse_addp();
	if (!addp) {
		/* TODO FREE mul WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_addp returned null\n");
		return NULL;
	}
	return ast_new(AST_ADD, mul, addp, 0);
}

ast_node*
parse_addp ()
{
	/* <Add'> ::= '+' <Add> */
	ast_node *res = ast_new(AST_ADDP, NULL, NULL, 0);
	if (expect(OP_ADD)) {
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
		res->op1 = ast_new(AST_EPSILON, NULL, NULL, 0);
	}
	return res;
}

ast_node*
parse_mul ()
{
	/* <Mul> ::= <Term> <Mul'> */
	ast_node* term = parse_term();
	if (!term) {
		/* TODO raise error */
		printf("Error: parse_term returned null\n");
		return NULL;
	}
	ast_node* mulp = parse_mulp();
	if (!mulp) {
		/* TODO FREE term WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_mulp returned null\n");
		return NULL;
	}
	return ast_new(AST_MUL, term, mulp, 0);
}

ast_node*
parse_mulp ()
{
	ast_node* res = ast_new(AST_MULP, NULL, NULL, 0);
	if (expect(OP_MUL)) {
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
		res->op1 = ast_new(AST_EPSILON, NULL, NULL, 0);
	}
	return res;
}

ast_node*
parse_term ()
{
	/* <Term> ::= <Num> */
	if (expect(INTEGER)) {
		printf("Info: Num found\n");
		ast_node* num = ast_new(AST_NUM, NULL, NULL, tokens->num);
		tokens = tk_pop_ll(tokens);
		return ast_new(AST_TERM, num, NULL, 0);
	/* Term ::= '(' <Add> ')' */
	} else if (expect(LPAREN)) {
		printf("Info: '(' found\n");
		tokens = tk_pop_ll(tokens);
		ast_node* add = parse_add();
		if (!add) {
			printf("Error: parse_add returned null\n");
			return NULL;
		}
		if (!expect(RPAREN)) {
			printf("Error: Expected ')'\n");
			return NULL;
		}
		tokens = tk_pop_ll(tokens);
		return ast_new(AST_TERM, add, NULL, 0);
	}
	/* TODO raise error */
	printf("Error: Expected Num not found\n");
	return NULL;
}

int
main ()
{
	token* list = tk_new(LPAREN, 0);
	tk_append_ll(list, tk_new(INTEGER, 1));
	tk_append_ll(list, tk_new(OP_ADD, 0));
	tk_append_ll(list, tk_new(INTEGER, 2));
	tk_append_ll(list, tk_new(RPAREN, 0));
	tk_append_ll(list, tk_new(OP_ADD, 0));
	tk_append_ll(list, tk_new(LPAREN, 0));
	tk_append_ll(list, tk_new(INTEGER, 3));
	tk_append_ll(list, tk_new(OP_ADD, 0));
	tk_append_ll(list, tk_new(INTEGER, 4));
	tk_append_ll(list, tk_new(RPAREN, 0));

	// token* src = tk_ll_to_arr(list);
	// int src_len = tk_len_ll(list);

	// parse_root(src, src_len);
	
	// tk_print_ll(list);

	ast_node* test = parse_root(list);
	ast_print_preorder(test, 0);
	// cst_print_node(test);

	// tk_delete_ll(list);

	// tk_print_arr(src, src_len);
	// free(src);
}
