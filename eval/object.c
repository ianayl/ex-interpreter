#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eval/object.h"

obj* 
obj_new(obj_type type, float num, char *str)
{
	obj *res = (obj*) malloc(sizeof(obj));
	res->type = type;
	if (type == OBJ_IDENIFIER) {
		res->str = (char*) calloc(strlen(str) + 1, sizeof(char));
		strcpy(res->str, str);
	} else {
		res->num = num;
	}
	return res;
}

obj*
obj_delete(obj *src)
{
	if (!src) return NULL;
	if (src->type == OBJ_IDENIFIER) free(src->str);
	free(src);
	return NULL;
}

void
obj_print(obj *src)
{
	if (!src) return;

	if (src->type == OBJ_IDENIFIER) {
		printf("Obj: Identifier: %s\n", src->str);
	} else if (src->type == OBJ_NUM) {
		printf("Obj: Num: %f\n", src->num);
	} else if (src->type == OBJ_NULL) {
		printf("Obj: Null\n");
	} else printf("Obj: Error: Unknown type\n");
}
