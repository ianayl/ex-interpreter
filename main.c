#include "eval/hashmap.h"
#include "eval/object.h"
#include "lexer/lexer.h"
#include "parser/ast_parser/ast_parser.h"
#include "eval/eval.h"
#include <stdio.h>
#include <sys/types.h>

#define SHELL_BUF_INCR 80
#define SHELL_PROMPT ">>> "

hashmap *heap;

char*
shell_readline()
{
	printf(SHELL_PROMPT);

	char* buf = (char*) malloc(SHELL_BUF_INCR * sizeof(char));
	int buf_size = SHELL_BUF_INCR;
	int i = 0;
	char c;
	while ((c = getchar()) != '\n' && c != '\0' && c != EOF) {
		buf[i++] = c;
		if (i == buf_size) {
			buf_size = buf_size + SHELL_BUF_INCR;
			buf = (char*) realloc(buf, buf_size + SHELL_BUF_INCR);
		}
	}
	buf[i] = '\0';

	return buf;
}

int
main (int argc, char** argv)
{
	printf("Experimental Interpreter: A toy interpreter for learning\n");

	if (argc < 1) {
		fprintf(stderr, "Error: Not implemented yet.\n");
		return -1;
	}

	printf("Type 'exit' to exit the interactive shell.\n");

	heap = hm_new(HM_INITIAL_SIZE);

	char* input;
	u_int8_t shell_continue = 1;
	while(shell_continue) {

		/* TODO this is ugly, don't do this, add returns lol */
		input = shell_readline();
		if (!strcmp(input, "exit")) {
			shell_continue = 0;
			free(input);
			break;
		}

		printf("==> Lex output: ----------------------------------\n");
		token *list = lex(input);
		free(input);
		tk_print_ll(list);

		printf("==> Parse output: --------------------------------\n");
		/* NOTE: NO NEED TO FREE LIST: PARSER FREES AUTOMATICALLY */
		ast_node *test = parse_root(list);
		ast_print_preorder(test, 0);

		printf("==> Evaluation: ----------------------------------\n");
		obj *res = eval_ast(heap, test);
		printf("Evaluated result: ");
		obj_print(res);
		res = obj_delete(res);
		printf("Heap dump:\n");
		hm_print(heap);
		test = ast_free(test);
		printf("==> End. -----------------------------------------\n");
	}
	heap = hm_clear(heap);
}
