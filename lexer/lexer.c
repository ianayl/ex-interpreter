#include "lexer/lexer.h"
#include <stdlib.h>
#include <stdio.h>

token*
_lex_new_tk (token *head, tk_type cur_type, char* buf)
{
	if (cur_type == NULL_TOKEN) return head;
	int num = (cur_type == INTEGER) ? num = atoi(buf) : 0;
	return tk_append_ll(head, tk_new(cur_type, num));
}

void
_lex_reset_buf (tk_type *cur_type, int *buf_len, int *buf_pos, char* *buf)
{
	*cur_type = NULL_TOKEN;
	*buf_len = LEXER_BUF_INCR;
	*buf_pos = 0;
	free(*buf);
	*buf = (char*) calloc(*buf_len, sizeof(char));
}

token*
lex (char* src)
{
	token *res = NULL;

	tk_type cur_type = NULL_TOKEN;
	int buf_len = LEXER_BUF_INCR;
	int buf_pos = 0;
	char* buf = (char*) calloc(buf_len, sizeof(char));

	for (; *src != '\0'; src++) {
		if (buf_pos >= buf_len - 1) {
			buf_len += LEXER_BUF_INCR;
			buf = (char*) reallocarray(buf, buf_len, sizeof(char));
		}

		if (*src >= '0' && *src <= '9') {
			if (cur_type == INTEGER) buf[buf_pos++] = *src;
			else {
				res = _lex_new_tk(res, cur_type, buf);
				_lex_reset_buf(&cur_type, &buf_len, &buf_pos,
					       &buf);
				cur_type = INTEGER;
				buf[buf_pos++] = *src;
			}
		} else if (*src == '+') {
			res = _lex_new_tk(res, cur_type, buf);
			res = _lex_new_tk(res, OP_ADD, "+");
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '*') {
			res = _lex_new_tk(res, cur_type, buf);
			res = _lex_new_tk(res, OP_MUL, "*");
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '(') {
			res = _lex_new_tk(res, cur_type, buf);
			res = _lex_new_tk(res, LPAREN, "(");
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == ')') {
			res = _lex_new_tk(res, cur_type, buf);
			res = _lex_new_tk(res, RPAREN, ")");
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else {
			printf("Lexer: Unknown character, ignoring\n");
			res = _lex_new_tk(res, cur_type, buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		}
	}

	if (buf_pos != 0) res = _lex_new_tk(res, cur_type, buf);
	free(buf);

	return res;
}
