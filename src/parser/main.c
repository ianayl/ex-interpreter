#include "tokens.h"

#include <stdio.h>

int 
main ()
{
	token* list = tk_new(INTEGER, 4);
	tk_append(list, tk_new(OP_ADD, 0));
	tk_append(list, tk_new(INTEGER, 2));
	tk_append(list, tk_new(OP_MUL, 0));
	tk_append(list, tk_new(INTEGER, 0));

	tk_print_arr(list);

	printf("len: %d\n", tk_len(list));

	tk_delete_arr(list);
}
