#include "lexer/lexer.h"
#include "parser/ast_parser/ast_parser.h"

int
main (int argc, char** argv)
{
	printf("Experimental Interpreter: A toy interpreter for learning\n");

	printf("==> Lex output: ------------------------------------------\n");
	if (argc <= 1) {
		fprintf(stderr, "Error: Nothing to lex.\n");
		return -1;
	}
	token* list = lex(argv[1]);
	tk_print_ll(list);

	printf("==> Parse output: ----------------------------------------\n");
	/* NOTE: NO NEED TO FREE LIST: PARSER FREES LIST AUTOMATICALLY */
	ast_node* test = parse_root(list);
	ast_print_preorder(test, 0);

	printf("==> End. --------------------------------------------------\n");
	test = ast_free(test);
}

