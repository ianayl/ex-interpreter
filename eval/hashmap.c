#include "eval/hashmap.h"

hashmap*
hm_new()
{
	hashmap* res = (hashmap*) malloc(sizeof(hashmap));
	/* Hopefully calloc initializes everything to NULL? */
	res->entries = (hm_entry**) calloc(HM_INITIAL_SIZE, sizeof(hm_entry*));
	res->size = HM_INITIAL_SIZE;
	res->occupied = 0;
	return res;
}
