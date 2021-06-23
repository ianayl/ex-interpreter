#include "parser/ast_parser/ast_parser.h"
#include "parser/ast_parser/ast.h"

token* tokens = NULL;
ast_node* epsilon;

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
	epsilon = ast_new(AST_EPSILON, NULL, NULL, 0);

	ast_node *res = parse_add();
	free(epsilon);

	if (!res) {
		/* TODO raise error: Invalid parse */
		printf("Error: tree is null\n");
	} else if (tokens) {
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
	
	/* No addition, pass on mul */
	} else if (addp == epsilon) return mul;

	/* Handle addition */
	return ast_new(AST_ADD, mul, addp, 0);
}

ast_node*
parse_addp ()
{
	/* <Add'> ::= '+' <Add> */
	if (expect(OP_ADD)) {
		printf("Info: Expected '+' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *res = parse_add(); 
		if (!res) {
			printf("Error: parse_add returned null\n");
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}
		return res;
	}

	/* <Mul'> ::= <Epsilon> */
	printf("Info: '+' not found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_mul ()
{
	/* <Mul> ::= <Term> <Mul'> */
	ast_node *term = parse_term();
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

	/* No multiplication, pass on term */
	} else if (mulp == epsilon) return term;

	/* Handle multiplication */
	return ast_new(AST_MUL, term, mulp, 0);
}

ast_node*
parse_mulp ()
{
	/* <Mul'> ::= '*' <Mul> */
	if (expect(OP_MUL)) {
		printf("Info: Expected '*' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *res = parse_mul();
		if (!res) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_mul returned null\n");
			return NULL;
		}
		return res;
	}

	/* <Mul'> ::= <Epsilon> */
	printf("Info: '*' not found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_term ()
{
	/* <Term> ::= <Num> */
	if (expect(INTEGER)) {
		printf("Info: Num found\n");
		ast_node* num = ast_new(AST_NUM, NULL, NULL, tokens->num);
		tokens = tk_pop_ll(tokens);
		return num;

	/* Term ::= '(' <Add> ')' */
	} else if (expect(LPAREN)) {
		printf("Info: '(' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node* add = parse_add();
		if (!add) {
			printf("Error: parse_add returned null\n");
			return NULL;

		} else if (!expect(RPAREN)) {
			printf("Error: Expected ')'\n");
			return NULL;
		}

		tokens = tk_pop_ll(tokens);
		return add;
	}

	/* TODO raise error */
	printf("Error: Expected Num not found\n");
	return NULL;
}

// int
// main ()
// {
// 	token* list = NULL; 
// 	list = tk_append_ll(list, tk_new(INTEGER, 1));
// 	list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	list = tk_append_ll(list, tk_new(INTEGER, 2));
// 	list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	list = tk_append_ll(list, tk_new(INTEGER, 3));
// 	list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	list = tk_append_ll(list, tk_new(INTEGER, 4));
// 
// 	tk_print_ll(list);
// 	ast_node* test = parse_root(list);
// 	ast_print_preorder(test, 0);
// 	test = ast_free(test);
// 	// tk_delete_ll(list);
// 
// 	/* CAUTION:
// 	 *
// 	 * 1 + 2 * 3 + 4:
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 1));
// 	 * list = tk_append_ll(list, tk_new(OP_ADD, 0));
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 2));
// 	 * list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 3));
// 	 * list = tk_append_ll(list, tk_new(OP_ADD, 0));
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 4));
// 	 *
// 	 * Expected:
// 	 * (1 + (2*3)) + 4
// 	 *
// 	 * Got:
// 	 * 1 + ((2*3) + 4)
// 	 *
// 	 * 1 * 2 * 3 * 4:
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 1));
// 	 * list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 2));
// 	 * list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 3));
// 	 * list = tk_append_ll(list, tk_new(OP_MUL, 0));
// 	 * list = tk_append_ll(list, tk_new(INTEGER, 4));
// 	 *
// 	 * Expected:
// 	 * ((1*2)*3)*4
// 	 *
// 	 * Got:
// 	 * 1*(2*(3*4))
// 	 */
// 
// }
