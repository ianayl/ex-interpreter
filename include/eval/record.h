#ifndef RECORD_H
#define RECORD_H

/* 
 * Activation record -- header file 
 *
 * Note that we're using parent-pointer trees instead of a stack.
 */
// TODO: is this really required? This allows wilder ways to execute functions,
//	 but what are the odds I'll actually need more than a stack?

#include <stdlib.h>
#include "eval/hashmap.h"

typedef struct record {
	hashmap *map;
	struct record *prev; /**< pointer to the parent of the tree */
	int indent_lvl;      /**< Indentation within the code of the record */
} record;

/** 
 * Construct a new activation record
 *
 * @param prev parent of the activation record
 * @param indent_lvl indentation associated with in the code of the record. This
 *		     is so that scope lines up.
 */
record* record_new(record *prev, int indent_lvl);

/**
 * Delete/Free the activation record
 *
 * @param src the activation record to delete
 */
record* record_free(record *src);

#endif
