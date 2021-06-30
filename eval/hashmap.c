#include "eval/hashmap.h"
#include <stdlib.h>
#include <string.h>

unsigned long
hm_hash(hashmap *src, char* key)
{
	/* Using fnv-1a */
	unsigned long hash = HM_FNV_OFFSET_BASIS;

	for (; *key != '\0'; key++) {
		hash ^= *key;
		hash *= HM_FNV_PRIME;
	}

	return hash % src->size;
}

hashmap*
hm_new()
{
	hashmap *res = (hashmap*) malloc(sizeof(hashmap));
	/* Hopefully calloc initializes everything to NULL? */
	res->entries = (hm_entry**) calloc(HM_INITIAL_SIZE, sizeof(hm_entry*));
	res->size = HM_INITIAL_SIZE;
	res->occupied = 0;
	return res;
}

hm_entry*
hm_new_pair(char* key, obj *val)
{
	hm_entry* res = (hm_entry*) malloc(sizeof(hm_entry));

	/* 
	 * Copying because I don't know if key is a string literal or not, thus
	 * easier to just malloc and free always
	 *
	 * TODO reconsider: Do I need calloc here? does strcpy place \0's? 
	 */
	res->key = (char*) calloc(strlen(key) + 1, sizeof(char));
	strcpy(res->key, key);

	res->val = val;
	res->next = NULL;
	return res;
}

void
hm_set(hashmap *src, char* key, obj *val)
{
	unsigned long pos = hm_hash(src, key);

	if (!src->entries[pos]) {
		src->entries[pos] = hm_new_pair(key, val);
		src->occupied ++;
		return;
	}

	hm_entry *prev;
	for (hm_entry *p = src->entries[pos]; p; p = p->next) {
		if (!strcmp(p->key, key)) {
			/* 
			 * Only free and replace val if val is not the same,
			 * or else val itself gets freed
			 *
			 * TODO reconsider this behavior: val should probably 
			 * not be freed here - a garbage collector should be
			 * used instead
			 */
			if (p->val != val) {
				free(p->val);
				p->val = val;
			}
			return;
		}
		prev = p;
	}

	prev->next = hm_new_pair(key, val);
	src->occupied ++;
}

obj*
hm_get(hashmap *src, char* key)
{
	unsigned long pos = hm_hash(src, key);
	for (hm_entry *p = src->entries[pos]; p; p = p->next)
		if (!strcmp(p->key, key)) return p->val;
	return NULL;
}

void
hm_delete(hashmap *src, char* key)
{
	/*
	 * TODO reconsider the freeing behavior in this function:
	 * Once a garbage collector kicks in, freeing val should probably be 
	 * handled by the garbage collector. Remember to free hm_entry though.
	 */

	unsigned long pos = hm_hash(src, key);

	if (!src->entries[pos]) return;

	if (!strcmp(src->entries[pos]->key, key)) {
		hm_entry *next = src->entries[pos]->next;
		free(src->entries[pos]->key);
		free(src->entries[pos]->val);
		free(src->entries[pos]);
		src->entries[pos] = next;
		src->occupied --;
		return;
	}

	hm_entry *prev = src->entries[pos];
	for (hm_entry *p = prev->next; p; p = p->next)
		if (!strcmp(p->key, key)) {
			prev->next = p->next;
			free(p->key);
			free(p->val);
			free(p);
			src->occupied --;
			return;
		}
}

hashmap*
hm_clear(hashmap *src)
{
	/*
	 * TODO reconsider the freeing behavior in this function:
	 * Once a garbage collector kicks in, freeing val should probably be 
	 * handled by the garbage collector. Remember to free hm_entry though.
	 */

	for (int i = 0; i < src->size; i++) {
		hm_entry *tmp;
		while (src->entries[i]) {
			tmp = src->entries[i];
			src->entries[i] = src->entries[i]->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
		}
	}

	free(src->entries);
	free(src);
	return NULL;
}

void
hm_print(hashmap *src)
{
	if (!src) return;
	for (int i = 0; i < src->size; i++)
		for (hm_entry *p = src->entries[i]; p; p = p->next)
			printf("(%d)  %s: %f\n", i, p->key, p->val->num);
}

// int
// main()
// {
// 	hashmap *tmp = hm_new();
// 	obj *asdf = (obj*) malloc(sizeof(obj));
// 	asdf->num = 4;
// 	hm_set(tmp, "asdf", asdf);
// 	hm_print(tmp);
// 	asdf->num = 5;
// 	hm_set(tmp, "asdf", asdf);
// 	printf("\n");
// 	hm_print(tmp);
// 	obj *asdf1 = (obj*) malloc(sizeof(obj));
// 	asdf1->num = 7;
// 	hm_set(tmp, "asdf", asdf1);
// 	printf("\n");
// 	hm_print(tmp);
// 	obj *john = (obj*) malloc(sizeof(obj));
// 	john->num = 42;
// 	obj *a = (obj*) malloc(sizeof(obj));
// 	a->num = 231;
// 	obj *ptr = (obj*) malloc(sizeof(obj));
// 	ptr->num = 9;
// 	obj *im = (obj*) malloc(sizeof(obj));
// 	im->num = 27;
// 	hm_set(tmp, "john", john);
// 	hm_set(tmp, "ptr", ptr);
// 	hm_set(tmp, "a", a);
// 	hm_set(tmp, "im", im);
// 	printf("\n");
// 	hm_print(tmp);
// 	hm_delete(tmp, "a");
// 	printf("\n");
// 	hm_print(tmp);
// 	hm_delete(tmp, "im");
// 	printf("\n");
// 	hm_print(tmp);
// 	hm_delete(tmp, "im");
// 	printf("\n");
// 	hm_print(tmp);
// 	tmp = hm_clear(tmp);
// 	printf("\n");
// 	hm_print(tmp);
// }
