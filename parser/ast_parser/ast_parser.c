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
_parse_successor (ast_node *head)
{
	if (!head) return NULL;

	if (head->op1 == NULL)
		return head;
	return _parse_successor(head->op1);
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
	ast_node *successor = _parse_successor(addp);
	successor->op1 = mul;
	return addp;
}

ast_node*
parse_addp ()
{
	/* <Add'> ::= '+' <Mul> <Add'> */
	if (expect(OP_ADD)) {
		printf("Info: Expected '+' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *mul = parse_mul(); 
		if (!mul) {
			printf("Error: parse_term returned null\n");
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}

		ast_node *addp = parse_addp();
		if (!addp) {
			printf("Error: parse_addp returned null\n");
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}

		if (addp == epsilon) return ast_new(AST_ADD, NULL, mul, 0);
		else {
			ast_node *successor = _parse_successor(addp);
			successor->op1 = ast_new(AST_ADD, NULL, mul, 0);
			return addp;
		}

	/* <Add'> ::= '-' <Mul> <Add'> */
	} else if (expect(OP_SUB)) {
		printf("Info: Expected '-' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *mul = parse_mul(); 
		if (!mul) {
			printf("Error: parse_term returned null\n");
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}

		ast_node *addp = parse_addp();
		if (!addp) {
			printf("Error: parse_addp returned null\n");
			/* TODO FREE res */
			/* TODO raise error */
			return NULL;
		}

		if (addp == epsilon) return ast_new(AST_SUB, NULL, mul, 0);
		else {
			ast_node *successor = _parse_successor(addp);
			successor->op1 = ast_new(AST_SUB, NULL, mul, 0);
			return addp;
		}
	}

	/* <Add'> ::= <Epsilon> */
	printf("Info: no '+', '-' found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_mul ()
{
	/* <Mul> ::= <Exp> <Mul'> */
	ast_node *exp = parse_exp();
	if (!exp) {
		/* TODO raise error */
		printf("Error: parse_exp returned null\n");
		return NULL;
	}

	ast_node* mulp = parse_mulp();
	if (!mulp) {
		/* TODO FREE term WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_mulp returned null\n");
		return NULL;

	/* No multiplication, pass on term */
	} else if (mulp == epsilon) return exp;

	/* Handle multiplication */
	ast_node *successor = _parse_successor(mulp);
	successor->op1 = exp;
	return mulp;
}

ast_node*
parse_mulp ()
{
	/* <Mul'> ::= '*' <Exp> <Mul'> */
	if (expect(OP_MUL)) {
		printf("Info: Expected '*' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *exp = parse_exp();
		if (!exp) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_exp returned null\n");
			return NULL;
		}

		ast_node *mulp = parse_mulp();
		if (!mulp) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_mulp returned null\n");
			return NULL;
		}

		if (mulp == epsilon) return ast_new(AST_MUL, NULL, exp, 0);
		else {
			ast_node *successor = _parse_successor(mulp);
			successor->op1 = ast_new(AST_MUL, NULL, exp, 0);
			return mulp;
		}

	/* <Mul'> ::= '/' <Term> <Mul'> */
	} else if (expect(OP_DIV)) {
		printf("Info: Expected '/' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *exp = parse_exp();
		if (!exp) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_term returned null\n");
			return NULL;
		}

		ast_node *mulp = parse_mulp();
		if (!mulp) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_mulp returned null\n");
			return NULL;
		}

		if (mulp == epsilon) return ast_new(AST_DIV, NULL, exp, 0);
		else {
			ast_node *successor = _parse_successor(mulp);
			successor->op1 = ast_new(AST_DIV, NULL, exp, 0);
			return mulp;
		}
	}

	/* <Mul'> ::= <Epsilon> */
	printf("Info:  no '*', '/' found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_exp ()
{
	/* <Exp> ::= <Term> <Exp'> */
	ast_node *term = parse_term();
	if (!term) {
		/* TODO raise error */
		printf("Error: parse_term returned null\n");
		return NULL;
	}

	ast_node* expp = parse_expp();
	if (!expp) {
		/* TODO FREE term WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_expp returned null\n");
		return NULL;

	/* No exponents, pass on term */
	} else if (expp == epsilon) return term;

	/* Handle exponents */
	ast_node *successor = _parse_successor(expp);
	successor->op1 = term;
	return expp;
}

ast_node*
parse_expp ()
{
	/* <Exp'> ::= '^' <Term> <Exp'> */
	if (expect(OP_EXP)) {
		printf("Info: Expected '^' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *term = parse_term();
		if (!term) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_term returned null\n");
			return NULL;
		}

		ast_node *expp = parse_expp();
		if (!expp) {
			/* TODO FREE res */
			/* TODO raise error */
			printf("Error: parse_mulp returned null\n");
			return NULL;
		}

		if (expp == epsilon) return ast_new(AST_EXP, NULL, term, 0);
		else {
			ast_node *successor = _parse_successor(expp);
			successor->op1 = ast_new(AST_MUL, NULL, term, 0);
			return expp;
		}
	}

	/* <Exp'> ::= <Epsilon> */
	printf("Info:  no '^' found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_term ()
{
	/* <Term> ::= <Num> */
	if (expect(INTEGER)) {
		printf("Info: Num found\n");
		ast_node *num = ast_new(AST_NUM, NULL, NULL, tokens->num);
		tokens = tk_pop_ll(tokens);
		return num;

	/* Term ::= '-' <Term> */
	} else if (expect(OP_SUB)) {
		printf("Info: '-' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *term = parse_term();
		if (!term) {
			printf("Error: parse_term returned null\n");
			return NULL;
		}
		return ast_new(AST_NEG, term, NULL, 0);

	/* Term ::= '(' <Add> ')' */
	} else if (expect(LPAREN)) {
		printf("Info: '(' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *add = parse_add();
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
	printf("Error: No match for <Term> found\n");
	return NULL;
}
