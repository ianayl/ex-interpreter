#include "lexer/lexer.h"
#include <stdlib.h>
#include <stdio.h>

token*
_lex_new_tk (token *head, tk_type cur_type, char* *buf)
{
	float num = (cur_type == TOK_NUM) ? num = atof(*buf) : 0;
	if (cur_type == TOK_NULL) return head;
	else if (cur_type == TOK_IDENIFIER) {
		if (!strcmp(*buf, "return")) {
			free(*buf);
			*buf = (char*) calloc(LEXER_BUF_INCR, sizeof(char));
			/* TODO consider a common section to if any of the above conditions passed */
			return tk_append_ll(head, tk_new(TOK_RETURN, 0, ""));
		} else if (!strcmp(*buf, "fn")) {
			free(*buf);
			*buf = (char*) calloc(LEXER_BUF_INCR, sizeof(char));
			return tk_append_ll(head, tk_new(TOK_FN, 0, ""));
		}
	}
	return tk_append_ll(head, tk_new(cur_type, num, *buf));
}

void
_lex_reset_buf (tk_type *cur_type, int *buf_len, int *buf_pos, char* *buf)
{
	*cur_type = TOK_NULL;
	*buf_len = LEXER_BUF_INCR;
	*buf_pos = 0;
	free(*buf);
	*buf = (char*) calloc(*buf_len, sizeof(char));
}

token*
lex (char* src)
{
	token *res = NULL;

	tk_type cur_type = TOK_NULL;
	int buf_len = LEXER_BUF_INCR;
	int buf_pos = 0;
	char* buf = (char*) calloc(buf_len, sizeof(char));

	for (; *src != '\0'; src++) {
		if (buf_pos >= buf_len - 1) {
			buf_len += LEXER_BUF_INCR;
			buf = (char*) reallocarray(buf, buf_len, sizeof(char));
		}

		if ((*src >= '0' && *src <= '9') || *src == '.') {
			if (cur_type == TOK_NUM || cur_type == TOK_IDENIFIER)
				buf[buf_pos++] = *src;
			else {
				res = _lex_new_tk(res, cur_type, &buf);
				_lex_reset_buf(&cur_type, &buf_len, &buf_pos,
					       &buf);
				cur_type = TOK_NUM;
				buf[buf_pos++] = *src;
			}
		} else if  ((*src >= 'A' && *src <= 'Z') || 
			    (*src >= 'a' && *src <= 'z')) {
			if (cur_type == TOK_IDENIFIER) buf[buf_pos++] = *src;
			else {
				res = _lex_new_tk(res, cur_type, &buf);
				_lex_reset_buf(&cur_type, &buf_len, &buf_pos,
					       &buf);
				cur_type = TOK_IDENIFIER;
				buf[buf_pos++] = *src;
			}
		} else if (*src == '=') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_ASSIGNMENT, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '+') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_ADD, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '-') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_SUB, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '*') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_MUL, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '/') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_DIV, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '^') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_EXP, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '%') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_MOD, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == '(') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_LPAREN, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == ')') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_RPAREN, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else if (*src == ',') {
			res = _lex_new_tk(res, cur_type, &buf);
			res = _lex_new_tk(res, TOK_COMMA, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		} else {
			printf("Lexer: Unknown character, ignoring\n");
			res = _lex_new_tk(res, cur_type, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		}
	}

	if (buf_pos != 0) res = _lex_new_tk(res, cur_type, &buf);
	free(buf);

	return res;
}
