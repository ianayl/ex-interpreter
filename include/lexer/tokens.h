#ifndef TOKENS_H
#define TOKENS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum token_type {
	TOK_NULL,
	TOK_NUM,
	TOK_IDENIFIER,
	TOK_ASSIGNMENT,
	TOK_ADD,
	TOK_SUB,
	TOK_MUL,
	TOK_DIV,
	TOK_EXP,
	TOK_MOD,
	TOK_LPAREN,
	TOK_RPAREN
} tk_type;

typedef struct token {
	tk_type type;
	union {
		float num;
		char* str;
	};
	struct token* next;
} token;

token* tk_new (tk_type type, float num, char* str);

token* tk_append_ll (token *head, token *n);

token* tk_delete_ll (token *head);

int tk_len_ll (token *head);

void tk_print_ll (token *head);

token* tk_ll_to_arr (token *head);

void tk_print_arr (token* arr, int len);

token* tk_pop_ll (token *head);

#endif
