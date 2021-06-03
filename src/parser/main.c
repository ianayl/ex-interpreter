#include "tokens.h"

#include <stdio.h>

int 
main ()
{
	token* list = tk_new(INTEGER, 4);
	tk_append_ll(list, tk_new(OP_ADD, 0));
	tk_append_ll(list, tk_new(INTEGER, 2));
	tk_append_ll(list, tk_new(OP_MUL, 0));
	tk_append_ll(list, tk_new(INTEGER, 0));

	tk_print_ll(list);

	printf("len: %d\n", tk_len_ll(list));

	tk_delete_ll(list);
}
