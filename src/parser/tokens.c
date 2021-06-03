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
tk_append (token *head, token *n)
{
	if (!head) return n;

	for (; head->next; head = head->next);
	head->next = n;
	return head;
}

token*
tk_delete_arr (token *head)
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
tk_len (token *head)
{
	int res;
	for (res = 0; head; head = head->next)
		res ++;
	return res;
}

void
tk_print_arr (token *head)
{
	for (token* p = head; p; p = p->next) {
		if (p->type == INTEGER)
			printf("Type: INTEGER, num: %d\n", p->num);
		else if (p->type == OP_ADD)
			printf("Type: OP_ADD (+)\n");
		else if (p->type == OP_MUL)
			printf("Type: OP_MUL (*)\n");
		else if (p->type == NULL_TYPE)
			printf("Type: NULL_TYPE\n");
		else
			printf("Type: INVALID TYPE\n");
	}
}
