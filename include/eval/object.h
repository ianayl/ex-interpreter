#ifndef OBJECT_H
#define OBJECT_H

/* Objects (variables) -- header file */

typedef enum object_type {
	OBJ_NULL,
	OBJ_NUM,
	OBJ_IDENTIFIER, /**< Reference to another identifier */
} obj_type;

typedef struct object {
	obj_type type;
	union {
		float num;
		char* identifier;
		// TODO: this is a horrible way to implement references, rethink
		//       this part (if variables are stored on a heap later then
		//       why not just store heap addresses?)
	};
} obj;

/**
 * Create a new object -- only one value field (num, etc) will be used depending
 * on the type of the object
 *
 * @param type the type of the new object
 * @param num the numerical value of the new object (does not matter if variable
 *            is not a number)
 * @param identifier the identifier the new object refers to (does not matter if
 *                   variable is not a string)
 */
obj* obj_new(obj_type type, float num, char* identifier);

/** 
 * Delete/free an object
 *
 * @param src the object to delete
 * @return the new value of the pointer to the object to be deleted (usually NULL)
 */
obj* obj_delete(obj *src);

/** 
 * Print information about the object
 *
 * @param src the object to print
 */
void obj_print(obj *src);

#endif
