#ifndef RECORD_H
#define RECORD_H

#include <stdlib.h>
#include "eval/hashmap.h"

typedef struct record {
	hashmap *map;
	struct record *prev;
	int indent_lvl;
} record;

record* record_new(record *prev, int indent_lvl);
record* record_free(record *src);

#endif
