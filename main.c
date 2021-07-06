#include "eval/hashmap.h"
#include "eval/object.h"
#include "lexer/lexer.h"
#include "parser/ast_parser/ast_parser.h"
#include "eval/eval.h"

int
main (int argc, char** argv)
{
	printf("Experimental Interpreter: A toy interpreter for learning\n");

	printf("==> Lex output: ------------------------------------------\n");
	if (argc <= 1) {
		fprintf(stderr, "Error: Nothing to lex.\n");
		return -1;
	}
	token *list = lex(argv[1]);
	tk_print_ll(list);

	printf("==> Parse output: ----------------------------------------\n");
	/* NOTE: NO NEED TO FREE LIST: PARSER FREES LIST AUTOMATICALLY */
	ast_node *test = parse_root(list);
	ast_print_preorder(test, 0);

	printf("==> Evaluation: ------------------------------------------\n");
	hashmap *heap = hm_new(HM_INITIAL_SIZE);
	obj *res = eval_ast(heap, test);
	printf("Evaluated result: ");
	obj_print(res);
	res = obj_delete(res);
	printf("Heap dump:\n");
	hm_print(heap);
	test = ast_free(test);
	heap = hm_clear(heap);

	printf("==> End. --------------------------------------------------\n");
}

