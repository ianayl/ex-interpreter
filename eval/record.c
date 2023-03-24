#include "eval/record.h"

/*
 * Activation records (Stack frame) -- implementation code
 *
 * DOCUMENTATION FOR PUBLIC FUNCTIONS ARE LOCATED IN record.h INSTEAD
 * This is done so that language servers can pick up function descriptions
 */

record* record_new(record *prev, int indent_lvl)
{
	record *res = (record*) malloc(sizeof(record));
	res->map = hm_new(HM_INITIAL_SIZE);
	res->prev = prev;
	res->indent_lvl = indent_lvl;
	return res;
}

record* record_free(record *src)
{
	src->map = hm_clear(src->map);
	free(src);
	return NULL;
}
