#ifndef TOKENS_H
#define TOKENS_H

typedef enum token_type {
	NULL_TYPE,
	INTEGER,
	OP_ADD,
	OP_MUL
} tk_type;

typedef struct token {
	tk_type type;
	int num;
	struct token* next;
} token;

token* 
tk_new (tk_type type, int num);

token*
tk_append (token *head, token *n);

token*
tk_delete_arr (token *head);

int
tk_len (token *head);

void
tk_print_arr (token *head);

#endif
