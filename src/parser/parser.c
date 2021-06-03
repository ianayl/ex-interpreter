#include "tokens.h"

void 
parse_root (token *src)
{
	int cur_i;
	int len_src = tk_len(src);

}

int
main ()
{
	token* src = tk_new(INTEGER, 4);
	tk_append(src, tk_new(OP_ADD, 0));
	tk_append(src, tk_new(INTEGER, 2));
	tk_append(src, tk_new(OP_MUL, 0));
	tk_append(src, tk_new(INTEGER, 0));

	tk_delete_arr(src);
}
