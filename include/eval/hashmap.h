#ifndef HASHMAP_H
#define HASHMAP_H

/* TODO reconsider putting objects in eval.h as project expands */
#include <stdlib.h>
#include <string.h>
#include "eval/eval.h"

/* TODO definitely up this later */
#define HM_INITIAL_SIZE 10

#define HM_FNV_OFFSET_BASIS 2166136261
#define HM_FNV_PRIME 16777619

typedef struct hashmap_entry {
	char *key;
	obj *val;
	struct hashmap_entry *next;
} hm_entry;

typedef struct hashmap {
	hm_entry** entries;
	unsigned long occupied;
	unsigned long size; /* haha */
} hashmap;

unsigned long hm_hash();
hashmap* hm_new();

#endif
