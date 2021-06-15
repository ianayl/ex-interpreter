#include <stdlib.h>
#include <stdio.h>

#include "tokens.h"

token* 
tk_new (tk_type type, int num)
{
	token* res = (token*) malloc(sizeof(token));
	res->type = type;
	res->num = num;
	res->next = NULL;

	return res;
}

token*
tk_append_ll (token *head, token *n)
{
	if (!head) return n;

	for (; head->next; head = head->next);
	head->next = n;
	return head;
}

token*
tk_delete_ll (token *head)
{
	token *p;
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
		if (p->type == INTEGER)
			printf("Type: INTEGER, num: %d\n", p->num);
		else if (p->type == OP_ADD)
			printf("Type: OP_ADD (+)\n");
		else if (p->type == OP_MUL)
			printf("Type: OP_MUL (*)\n");
		else if (p->type == NULL_TOKEN)
			printf("Type: NULL_TOKEN\n");
		else
			printf("Type: INVALID TYPE\n");
	}
}

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

void
tk_print_arr (token* arr, int len)
{
	for (int i = 0; i < len; i++)
		if (arr[i].type == INTEGER)
			printf("Type: INTEGER, num: %d\n", arr[i].num);
		else if (arr[i].type == OP_ADD)
			printf("Type: OP_ADD (+)\n");
		else if (arr[i].type == OP_MUL)
			printf("Type: OP_MUL (*)\n");
		else if (arr[i].type == NULL_TOKEN)
			printf("Type: NULL_TOKEN\n");
		else
			printf("Type: INVALID TYPE\n");
}

/* Pops off the first element of the linkedlist */
token*
tk_pop_ll (token* head)
{
	if (!head)
		return NULL;
	token* res = head->next;
	free(head);
	return res;
}
