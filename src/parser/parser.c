#include "tokens.h"
#include <stdlib.h>

void 
parse_root (token* src, int len_src)
{
	int cur_i;
}

int
main ()
{
	token* list = tk_new(INTEGER, 4);
	tk_append_ll(list, tk_new(OP_ADD, 0));
	tk_append_ll(list, tk_new(INTEGER, 2));
	tk_append_ll(list, tk_new(OP_MUL, 0));
	tk_append_ll(list, tk_new(INTEGER, 0));

	token* src = tk_ll_to_arr(list);
	int src_len = tk_len_ll(list);

	parse_root(src, src_len);

	tk_delete_ll(list);

	tk_print_arr(src, src_len);
	free(src);
}
