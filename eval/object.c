#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eval/object.h"

obj* 
obj_new(obj_type type, float num, char *identifier)
{
	obj *res = (obj*) malloc(sizeof(obj));
	res->type = type;
	if (type == OBJ_IDENTIFIER) {
		res->identifier = (char*) calloc(strlen(identifier) + 1,
						 sizeof(char));
		strcpy(res->identifier, identifier);
	} else {
		res->num = num;
	}
	return res;
}

obj*
obj_delete(obj *src)
{
	if (!src) return NULL;
	if (src->type == OBJ_IDENTIFIER) free(src->identifier);
	free(src);
	return NULL;
}

void
obj_print(obj *src)
{
	if (!src) return;

	if (src->type == OBJ_IDENTIFIER) {
		printf("Obj: Identifier: %s\n", src->identifier);
	} else if (src->type == OBJ_NUM) {
		printf("Obj: Num: %f\n", src->num);
	} else if (src->type == OBJ_NULL) {
		printf("Obj: Null\n");
	} else printf("Obj: Error: Unknown type\n");
}
