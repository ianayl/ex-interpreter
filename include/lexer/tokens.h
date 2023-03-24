#ifndef TOKENS_H
#define TOKENS_H

/* Lexeme tokens -- header file */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Types of all valid lexemes in the language */
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
	TOK_RPAREN,
	TOK_COMMA,
	TOK_FN,
	TOK_RETURN
} tk_type;

typedef struct token {
	tk_type type;
	union {
		/* 
		 * Conventions:
		 * - If the type does not have a number or a string attribute,
		 *   then it has a num of 0
		 * - A type can only have either a numerical value or a string
		 *   value
		 */
		float num;
		char* str;
	};
	struct token* next;
} token;

/**
 * Construct a new token
 *
 * @param type type of the new token
 * @param num numerical value of the token (or 0 if it doesn't have a value)
 * @param str a pointer to a malloc'd string if the token has a string value
 * @return a pointer to a new token
 */
token* tk_new (tk_type type, float num, char* str);

/**
 * Append token n onto a token list head
 *
 * @param head pointer to the head of the token list to insert into
 * @param n the new node to insert onto the token list
 * @return a pointer to the new head of the list
 */
token* tk_append_ll (token *head, token *n);

/**
 * Delete a token list head and free all its tokens
 *
 * @param head the token list to delete
 * @return a pointer to the new head of the list (should be NULL)
 */
token* tk_delete_ll (token *head);

/**
 * Return the length of a token list head
 *
 * @param head the token list to count the length of
 */
int tk_len_ll (token *head);

/** 
 * Print the contents of a token list head
 *
 * @param head the token list to print out
 */
void tk_print_ll (token *head);

/**
 * DEPRECATED: STICK TO TOKEN LISTS INSTEAD
 *
 * Convert a token list to an array of tokens instead: May be faster for certain
 * applications when compared to a linked list
 *
 * @param head the token list to convert into an array
 */
token* tk_ll_to_arr (token *head);

/**
 * DEPRECATED: STICK TO TOKEN LISTS INSTEAD
 *
 * Print the contents of a token array
 *
 * @param arr the array to print out
 * @param len the length of the array
 */
void tk_print_arr (token* arr, int len);

/**
 * Pop the first element off the token list
 *
 * @param the token list to pop
 * @return a pointer to the new head of the list
 */
token* tk_pop_ll (token *head);

#endif
