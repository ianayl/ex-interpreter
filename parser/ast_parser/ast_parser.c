#include "parser/ast_parser/ast_parser.h"
#include "lexer/tokens.h"
#include "parser/ast_parser/ast.h"

/*
 * AST parser -- implementation code
 *
 * DOCUMENTATION FOR PUBLIC FUNCTIONS ARE LOCATED IN ast_parser.h INSTEAD
 * This is done so that language servers can pick up function descriptions
 */

token *tokens = NULL; /**< Pointer to token list to consume from */
ast_node* epsilon;    /**< An epsilon singleton that can be reused */

int 
expect(tk_type type, int lookup)
{
	token *check;
	for (check = tokens; lookup > 0; lookup --) {
		if (!check) return 0;
		check = check->next;
	}
	if (check && check->type == type) return 1;
	return 0;
}

/* 
 * Find the leftmost node in the given subtree head: used to stitch AST's so
 * that they make sense
 */
ast_node*
_parse_successor(ast_node *head)
{
	if (!head) return NULL;

	if (head->op1 == NULL)
		return head;
	return _parse_successor(head->op1);
}

ast_node* 
parse_root(token *head, int *expect_indent)
{
	tokens = head;
	/* Initialize a single epsilon to save the malloc's for new epsilon's */
	epsilon = ast_new(AST_EPSILON, NULL, NULL, 0, "");

	/* Commence the parsing with the first derivation: */
	ast_node *res = parse_expr(expect_indent);
	free(epsilon);

	if (!res) {
		/* TODO raise error: Invalid parse */
		printf("Error: tree is null\n");

	/* If head is not null: tokens left over */
	} else if (tokens) {
		/* TODO raise error: Unfinished grammar */
		printf("Error: tokens left. LEFTOVER TOKENS:\n");
		tk_print_ll(tokens);
	}
	/* TODO hide debug output */
	tk_print_ll(tokens);
	return res;
}

ast_node*
parse_expr(int *expect_indent)
{
	/* <Expr> ::= 'fn' <Identifier> '(' <Params> ')' '=' */
	/* <Expr> ::= 'fn' <Identifier> '(' <Params> ')' '=' <Assign> */
	if (expect(TOK_FN, 0)) {
		printf("Info: 'fn' keyword found\n");
		tokens = tk_pop_ll(tokens);

		if (!expect(TOK_IDENIFIER, 0)) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: Expected identifier\n");
			return NULL;
		}
		ast_node *fn_name = ast_new(AST_IDENTIFIER, NULL, NULL, 0,
				            tokens->str);
		tokens = tk_pop_ll(tokens);

		if (!expect(TOK_LPAREN, 0)) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: Expected '('\n");
			return NULL;
		}
		tokens = tk_pop_ll(tokens);

		ast_node *params = parse_param();
		if (!params) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: parse_param returned null\n");
			return NULL;
		} else if (params == epsilon) params = NULL;

		if (!expect(TOK_RPAREN, 0)) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: Expected ')'\n");
			return NULL;
		}
		tokens = tk_pop_ll(tokens);
		
		if (!expect(TOK_ASSIGNMENT, 0)) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: Expected '='\n");
			return NULL;
		}
		tokens = tk_pop_ll(tokens);

		/* Assume nothing after '=' initially, then check for tokens */
		ast_node *assign = epsilon;
		/* <Expr> ::= 'fn' <Identifier> '(' <Params> ')' '=' */
		if (!tokens) *expect_indent = 1;
		/* <Expr> ::= 'fn' <Identifier> '(' <Params> ')' '=' <Assign> */
		else if (!(assign = parse_assign())) {
				/* TODO FREE WITH SOME SORT OF FN HERE */
				/* TODO raise error */
				printf("Error: parse_assign returned null\n");
				return NULL;
		}

		/* 
		 * ASTLIST structure:
		 * op1 = NULL 
		 * op2 = next node 
		 * ast = ast itself
		 */
		ast_node *fn_asts = NULL;
		if (assign != epsilon) {
			fn_asts = ast_new(AST_ASTLIST, NULL, NULL, 0, "");
			fn_asts->ast = assign;
		}
		ast_node *fn = ast_new(AST_FN, fn_name, fn_asts, 0, "");
		fn->params = params;
		return fn;
	}

	/* <Expr> ::= <Assign> */
	printf("Info: No 'fn', 'return' found, reducing to Assign\n");
	ast_node *assign = parse_assign();
	if (!assign) {
		/* TODO FREE mul WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_assign returned null\n");
		return NULL;
	}
	return assign;
}

ast_node*
parse_param()
{
	/* <Param> ::= <Identifier> <Param'> */
	if (expect(TOK_IDENIFIER, 0)) {
		printf("Info: Expected identifier found: %s\n", tokens->str);
		ast_node *identifier = ast_new(AST_PARAMLIST, NULL, NULL, 0,
					       tokens->str);
		tokens = tk_pop_ll(tokens);
		ast_node *paramp = parse_paramp();
		if (!paramp) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: parse_paramp returned null\n");
			return NULL;
		} else if (paramp != epsilon) identifier->next = paramp;

		return identifier;
	}
	
	/* <Param> ::= ε */
	printf("Info: No identifier found, reducing to epsilon\n");
	return epsilon;
	/* 
	 * TODO if expecting ε might be wise to check ahead for ')' now as
	 * then error message can say something like "Expected identifier, not
	 * expression in function declaration"
	 */
}

ast_node*
parse_paramp()
{
	/* <Param'> ::= ',' <Identifier> <Param'> */
	if (expect(TOK_COMMA, 0)) {
		printf("Info: Expected ',' found\n");
		tokens = tk_pop_ll(tokens);

		if (!expect(TOK_IDENIFIER, 0)) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: Expected identifier not found\n");
			return NULL;
		}
		ast_node *identifier = ast_new(AST_PARAMLIST, NULL, NULL, 0,
					       tokens->str);
		tokens = tk_pop_ll(tokens);

		ast_node *paramp = parse_paramp();
		if (!paramp) {
			/* TODO FREE WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: parse_paramp returned null\n");
			return NULL;
		} else if (paramp != epsilon) identifier->next = paramp;

		return identifier;
	}

	/* <Param'> ::= ε */
	printf("Info: No ',' found, reducing to epsilon\n");
	return epsilon;
	/* 
	 * TODO if expecting ε might be wise to check ahead for ')' now as
	 * then error message can say something like "Expected identifier, not
	 * expression in function declaration"
	 */
}

ast_node*
parse_assign()
{
	/* <Assign> ::= <Identifier> '=' <Identifier> */
	if (expect(TOK_IDENIFIER, 0) && expect(TOK_ASSIGNMENT, 1)) {
		printf("Info: Expected \"<Identifier> '='\" pattern found\n");
		ast_node *identifier = ast_new(AST_IDENTIFIER, NULL, NULL, 0,
					       tokens->str);
		tokens = tk_pop_ll(tokens);
		tokens = tk_pop_ll(tokens);

		ast_node *assign = parse_assign();
		if (!assign) {
			/* TODO FREE mul WITH SOME SORT OF FN HERE */
			/* TODO raise error */
			printf("Error: parse_assign returned null\n");
			return NULL;
		}

		return ast_new(AST_ASSIGNMENT, identifier, assign, 0, "");
	}

	/* <Assign> ::= <Add> */
	printf("Info: No identifier found, reducing to Add\n");
	ast_node *add = parse_add();
	if (!add) {
		/* TODO FREE mul WITH SOME SORT OF FN HERE */
		/* TODO raise error */
		printf("Error: parse_add returned null\n");
		return NULL;
	}
	return add;
}

ast_node*
parse_add()
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
parse_addp()
{
	/* <Add'> ::= '+' <Mul> <Add'> */
	if (expect(TOK_ADD, 0)) {
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

		if (addp == epsilon) return ast_new(AST_ADD, NULL, mul, 0, "");
		else {
			ast_node *successor = _parse_successor(addp);
			successor->op1 = ast_new(AST_ADD, NULL, mul, 0, "");
			return addp;
		}

	/* <Add'> ::= '-' <Mul> <Add'> */
	} else if (expect(TOK_SUB, 0)) {
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

		if (addp == epsilon) return ast_new(AST_SUB, NULL, mul, 0, "");
		else {
			ast_node *successor = _parse_successor(addp);
			successor->op1 = ast_new(AST_SUB, NULL, mul, 0, "");
			return addp;
		}
	}

	/* <Add'> ::= <Epsilon> */
	printf("Info: no '+', '-' found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_mul()
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
parse_mulp()
{
	/* <Mul'> ::= '*' <Exp> <Mul'> */
	if (expect(TOK_MUL, 0)) {
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

		if (mulp == epsilon) return ast_new(AST_MUL, NULL, exp, 0, "");
		else {
			ast_node *successor = _parse_successor(mulp);
			successor->op1 = ast_new(AST_MUL, NULL, exp, 0, "");
			return mulp;
		}

	/* <Mul'> ::= '/' <Term> <Mul'> */
	} else if (expect(TOK_DIV, 0)) {
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

		if (mulp == epsilon) return ast_new(AST_DIV, NULL, exp, 0, "");
		else {
			ast_node *successor = _parse_successor(mulp);
			successor->op1 = ast_new(AST_DIV, NULL, exp, 0, "");
			return mulp;
		}

	/* <Mul'> ::= '%' <Term> <Mul'> */
	} else if (expect(TOK_MOD, 0)) {
		printf("Info: Expected '%%' found\n");
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

		if (mulp == epsilon) return ast_new(AST_MOD, NULL, exp, 0, "");
		else {
			ast_node *successor = _parse_successor(mulp);
			successor->op1 = ast_new(AST_MOD, NULL, exp, 0, "");
			return mulp;
		}
	}

	/* <Mul'> ::= <Epsilon> */
	printf("Info: no '*', '/' found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_exp()
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
parse_expp()
{
	/* <Exp'> ::= '^' <Term> <Exp'> */
	if (expect(TOK_EXP, 0)) {
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

		if (expp == epsilon) return ast_new(AST_EXP, NULL, term, 0, "");
		else {
			ast_node *successor = _parse_successor(expp);
			successor->op1 = ast_new(AST_MUL, NULL, term, 0, "");
			return expp;
		}
	}

	/* <Exp'> ::= <Epsilon> */
	printf("Info: no '^' found, reducing to epsilon\n");
	return epsilon;
}

ast_node*
parse_term()
{
	/* <Term> ::= <Num> */
	if (expect(TOK_NUM, 0)) {
		printf("Info: Num found\n");
		ast_node *num = ast_new(AST_NUM, NULL, NULL, tokens->num, "");
		tokens = tk_pop_ll(tokens);
		return num;

	} else if (expect(TOK_IDENIFIER, 0)) {
		printf("Info: Identifier found\n");
		ast_node *identifier = ast_new(AST_IDENTIFIER, NULL, NULL, 0,
					       tokens->str);
		tokens = tk_pop_ll(tokens);
		return identifier;

	/* Term ::= '-' <Term> */
	} else if (expect(TOK_SUB, 0)) {
		printf("Info: '-' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *term = parse_term();
		if (!term) {
			printf("Error: parse_term returned null\n");
			return NULL;
		}
		return ast_new(AST_NEG, term, NULL, 0, "");

	/* Term ::= '(' <Assign> ')' */
	} else if (expect(TOK_LPAREN, 0)) {
		printf("Info: '(' found\n");
		tokens = tk_pop_ll(tokens);

		ast_node *assign = parse_assign();
		if (!assign) {
			printf("Error: parse_assign returned null\n");
			return NULL;

		} else if (!expect(TOK_RPAREN, 0)) {
			printf("Error: Expected ')'\n");
			return NULL;
		}

		tokens = tk_pop_ll(tokens);
		return assign;
	}

	/* TODO raise error */
	printf("Error: No match for <Term> found\n");
	return NULL;
}
