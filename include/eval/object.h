#ifndef OBJECT_H
#define OBJECT_H

typedef enum object_type {
	OBJ_NULL,
	OBJ_NUM,
	OBJ_IDENIFIER,
} obj_type;

typedef struct object {
	obj_type type;
	union {
		float num;
		char* str;
	};
} obj;

obj* obj_new(obj_type type, float num, char* str);
obj* obj_delete(obj *src);
void obj_print(obj *src);

#endif
