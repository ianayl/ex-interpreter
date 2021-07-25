#ifndef OBJECT_H
#define OBJECT_H

typedef enum object_type {
	OBJ_NULL,
	OBJ_NUM,
	OBJ_IDENTIFIER,
} obj_type;

typedef struct object {
	obj_type type;
	union {
		float num;
		char* identifier;
	};
} obj;

obj* obj_new(obj_type type, float num, char* identifier);
obj* obj_delete(obj *src);
void obj_print(obj *src);

#endif
