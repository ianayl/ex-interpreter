#ifndef HASHMAP_H
#define HASHMAP_H

/*
 * Hashmap -- header file
 *
 * Remember / Specifications:
 * - Separate chaining is used to resolve conflicts
 *   (Consider: a change to open addressing)
 * - Hashmap is dynamically resized when load hits HM_LOAD_THRESHOLD
 * - FNV-1a is the hash function
 */

#include "eval/object.h"

/* TODO definitely up this later */
#define HM_INITIAL_SIZE 100
#define HM_EXPAND_FACTOR 2

/* Maximum allowable load factor on the hashmap */
#define HM_LOAD_THRESHOLD ((long double) 0.8)

/* Primes used for FNV-1a */
#define HM_FNV_OFFSET_BASIS 2166136261
#define HM_FNV_PRIME 16777619

/* Linked list in each hashmap entry as per separate chaining */
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

/** 
 * Hash function used to decide the position of entries in the hashmap
 *
 * @param src the hashmap in question
 * @param key the key (basically the identifier) for the hash entry in question
 * @return the position of the entry in the hashmap based on the identifier key
 */
unsigned long hm_hash(hashmap *src, char* key);

/**
 * Create a new hashmap
 * NOTE: TO HAVE GOOD RESULTS WITH HASH FUNCTIONS, IDEALLY THE SIZE OF A HASHMAP
 *       SHOULD BE PRIME
 *
 * @param initial_size the size of the new hashmap (ideally prime)
 */
hashmap* hm_new(unsigned long initial_size);

/**
 * Set a key in the hashmap to be the object val
 *
 * @param src the hashmap to insert/change
 * @param key the key to insert/change
 * @param val the object/variable to be set to the key
 * @return the pointer to the new hashmap (in case expansion is required)
 */
hashmap* hm_set(hashmap *src, char* key, obj *val);

/** 
 * Delete/Free the hashmap src
 * 
 * @param src the hashmap to free
 * @return the new value of the pointer to the hashmap (usually NULL)
 */
hashmap* hm_clear(hashmap *src);

/** 
 * Fetch the object stored in hashmap src at the given key
 *
 * @param src the hashmap to fetch from
 * @param key the key to fetch
 */
obj* hm_get(hashmap *src, char* key);

/** 
 * Print every entry in the hashmap
 *
 * @param src the hashmap to print out
 */
void hm_print(hashmap *src);

#endif
