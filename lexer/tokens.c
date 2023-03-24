#include "lexer/tokens.h"

/*
 * Lexeme tokens -- implementation code
 *
 * DOCUMENTATION FOR PUBLIC FUNCTIONS ARE LOCATED IN tokens.h INSTEAD
 * This is done so that language servers can pick up function descriptions
 */

token* 
tk_new (tk_type type, float num, char* str)
{
	token* res = (token*) malloc(sizeof(token));
	res->type = type;
	/* 
	 * If the token has a string value (only identifiers for now),
	 * allocate a new string for it
	 */
	if (type == TOK_IDENIFIER) {
		res->str = (char*) calloc(strlen(str) + 1, sizeof(char));
		strcpy(res->str, str);
	} else res->num = num;
	res->next = NULL;

	return res;
}

token*
tk_append_ll (token *head, token *n)
{
	if (!head) return n;

	token* p = head;
	/* Get to the end the linked list */
	// TODO: Maybe keeping track of the tail of a token list isn't a shabby
	//       idea? but would involve more abstractions in the form of a struct
	for (; p->next; p = p->next);
	p->next = n;
	return head;
}

token*
tk_delete_ll (token *head)
{
	token *p; /* Previous node */
	/* As long as head isn't NULL (end of list), free the previous token */ 
	while (head) {
		p = head;
		head = head->next;
		free(p);
	}
	return NULL;
}

int
tk_len_ll (token *head)
{
	int res;
	for (res = 0; head; head = head->next)
		res ++;
	return res;
}

void
tk_print_ll (token *head)
{
	for (token* p = head; p; p = p->next) {
		if (p->type == TOK_NUM)
			printf("Type: TOK_NUM, num: %f\n", p->num);
		else if (p->type == TOK_IDENIFIER)
			printf("Type: TOK_IDENIFIER, str: %s\n", p->str);
		else if (p->type == TOK_ASSIGNMENT)
			printf("Type: TOK_ASSIGNMENT =\n");
		else if (p->type == TOK_ADD)
			printf("Type: TOK_ADD +\n");
		else if (p->type == TOK_SUB)
			printf("Type: TOK_SUB -\n");
		else if (p->type == TOK_MUL)
			printf("Type: TOK_MUL *\n");
		else if (p->type == TOK_DIV)
			printf("Type: TOK_DIV /\n");
		else if (p->type == TOK_EXP)
			printf("Type: TOK_EXP ^\n");
		else if (p->type == TOK_MOD)
			printf("Type: TOK_MOD %%\n");
		else if (p->type == TOK_LPAREN)
			printf("Type: TOK_LPAREN (\n");
		else if (p->type == TOK_RPAREN)
			printf("Type: TOK_RPAREN )\n");
		else if (p->type == TOK_FN)
			printf("Type: TOK_FN fn\n");
		else if (p->type == TOK_RETURN)
			printf("Type: TOK_RETURN return\n");
		else if (p->type == TOK_NULL)
			printf("Type: TOK_NULL\n");
		else
			printf("Type: INVALID TYPE\n");
	}
}

/* DEPRECATED - USE LINKED LISTS INSTEAD */
token*
tk_ll_to_arr (token *head)
{
	int len = tk_len_ll(head);
	token* res = (token*) malloc(sizeof(token) * len);
	for (int i = 0; i < len; i++) {
		res[i] = *head;
		head = head->next;
	}
	return res;
}

/* DEPRECATED - USE LINKED LISTS INSTEAD */
void
tk_print_arr (token* arr, int len)
{
	for (int i = 0; i < len; i++)
		if (arr[i].type == TOK_NUM)
			printf("Type: TOK_NUM, num: %f\n", arr[i].num);
		else if (arr[i].type == TOK_ADD)
			printf("Type: TOK_ADD +\n");
		else if (arr[i].type == TOK_MUL)
			printf("Type: TOK_MUL *\n");
		else if (arr[i].type == TOK_LPAREN)
			printf("Type: TOK_LPAREN (\n");
		else if (arr[i].type == TOK_RPAREN)
			printf("Type: TOK_RPAREN )\n");
		else if (arr[i].type == TOK_NULL)
			printf("Type: TOK_NULL\n");
		else
			printf("Type: INVALID TYPE\n");
}

/* Pops off the first element of the linkedlist */
token*
tk_pop_ll (token* head)
{
	if (!head)
		return NULL;
	token* res = head->next; /* New head is the next token */
	if (head->type == TOK_IDENIFIER) free(head->str);
	free(head);
	return res; /* Return new head */
}
