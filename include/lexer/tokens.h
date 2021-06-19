#ifndef TOKENS_H
#define TOKENS_H

typedef enum token_type {
	NULL_TOKEN,
	INTEGER,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	LPAREN,
	RPAREN
} tk_type;

typedef struct token {
	tk_type type;
	int num;
	struct token* next;
} token;

token* tk_new (tk_type type, int num);

token* tk_append_ll (token *head, token *n);

token* tk_delete_ll (token *head);

int tk_len_ll (token *head);

void tk_print_ll (token *head);

token* tk_ll_to_arr (token *head);

void tk_print_arr (token* arr, int len);

token* tk_pop_ll (token *head);

#endif
