#ifndef HASHMAP_H
#define HASHMAP_H

/* TODO reconsider putting objects in eval.h as project expands */
#include "eval/eval.h"

/* TODO definitely up this later */
#define HM_INITIAL_SIZE 10

typedef struct hashmap_entry {
	char *key;
	obj *val;
	struct hashmap_entry *next;
} hm_entry;

typedef struct hashmap {
	hm_entry** entries;
	long occupied;
	long size; /* haha */
} hashmap;

hashmap* hm_new();

#endif
