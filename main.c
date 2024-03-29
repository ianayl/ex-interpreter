#include <stdio.h>
#include <sys/types.h>
#include "eval/hashmap.h"
#include "eval/object.h"
#include "lexer/lexer.h"
#include "parser/ast_parser/ast_parser.h"
#include "eval/eval.h"
#include "eval/record.h"

#define SHELL_BUF_INCR 80
#define SHELL_PROMPT_ROOT ">>> "
#define SHELL_PROMPT_INDENT "... "

/* root "stack frames" / "activation record" - contains hashmap */
record *root_rec;

/* Status flags for the interpreter */
// TODO: eventually read from command line arugments instead
u_int8_t use_shell = 1;
u_int8_t debug = 1;

/* Fill buffer with input from stdin */
char*
shell_readline()
{
	char* buf = (char*) malloc(SHELL_BUF_INCR * sizeof(char));
	int buf_size = SHELL_BUF_INCR;
	int i = 0;
	char c;
	/* While there is still input, keep filling up buffer */
	while ((c = getchar()) != '\n' && c != '\0' && c != EOF) {
		buf[i++] = c;
		if (i == buf_size) { /* Buffer full, dynamically reallocate */
			buf_size = buf_size + SHELL_BUF_INCR;
			buf = (char*) realloc(buf, buf_size + SHELL_BUF_INCR);
		}
	}
	buf[i] = '\0';

	return buf;
}

/* Process one line of input from the shell, and produce a parse tree */
ast_node*
shell_getline(record *rec, int indent_lvl)
{
	if (!indent_lvl) printf(SHELL_PROMPT_ROOT);
	else printf(SHELL_PROMPT_INDENT);
	// printf(SHELL_PROMPT_ROOT);

	char *input = shell_readline();
	if (debug) {
		printf("==> Lex output: ----------------------------------\n");
		printf("Indent level: %d\n", lex_indent_lvl(input));
	}

	/*
	 * READ-EVALUATE-PRINT LOOP STARTS HERE
	 */
	token *list = lex(input); /* Lexer */
	free(input);
	if (debug) tk_print_ll(list);

	if (debug)
		printf("==> Parse output: --------------------------------\n");
	/* NOTE: No need to free list: parser frees list automatically */
	int expect_indent = 0;
	ast_node *res = parse_root(list, &expect_indent); /* Parser */
	if (debug) {
		ast_print_preorder(res, 0);
		printf("Expect indent: %s\n", (expect_indent) ? "YES" : "NO");
	}

	/* Incase an indented line is expected: */
	ast_node *tmp;
	while (expect_indent) {
		/* Keep reading */
		tmp = shell_getline(rec, indent_lvl + 1);
		if (!tmp) {
			expect_indent = 0;
			continue;
		} else if (res->op2->type == AST_ASTLIST) {
		} else {
			printf("Error: unknown AST tree type for indent\n");
			expect_indent = 0;
			continue;
		}
	}

	return res;
}

int
main(int argc, char** argv)
{
	printf("Experimental Interpreter: A toy interpreter for learning\n");

	/* TODO accomidate reading from a file */
	if (argc < 1) {
		fprintf(stderr, "Error: Not implemented yet.\n");
		return -1;
	}

	root_rec = record_new(NULL, 0);

	/* TODO accomidate reading from a file */
	u_int8_t shell_continue = 1;
	while(shell_continue) {

		/* 
		 * NOTE: REPL loop actually begins here, lexing and parsing are
		 * both handled here already.
		 */
		ast_node *test = shell_getline(root_rec, 0);

		if (debug)
			printf("==> Evaluation: ----------------------------------\n");
		obj *res = eval_ast(root_rec->map, test); /* Evaluation */
		if (debug) {
			printf("Evaluated result: ");
			obj_print(res);
			/* Clean up */
			res = obj_delete(res);
			printf("Heap dump:\n");
			hm_print(root_rec->map);
			test = ast_free(test);
			printf("==> End. -----------------------------------------\n");
		} else {
			if (res) printf("\nRESULT: ");
			obj_print(res);
		}
	}

	/* Root activation record no longer needed */
	root_rec = record_free(root_rec);
}
