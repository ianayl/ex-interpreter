#include "lexer/lexer.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Lexer -- implementation code
 *
 * DOCUMENTATION FOR PUBLIC FUNCTIONS ARE LOCATED IN lexer.h INSTEAD
 * This is done so that language servers can pick up function descriptions
 */

/* Add a new token onto the token list head */
token*
_lex_new_tk(token *head, tk_type cur_type, char* *buf)
{
	float num = (cur_type == TOK_NUM) ? num = atof(*buf) : 0;
	// TODO: tokens shouldn't have null. Handle an error instead later
	if (cur_type == TOK_NULL) return head; 
	/* 
	 * Lexer itself doesn't distinguish between keywords and identifiers.
	 * Do this here to relinquish responsibility from lexer.
	 */
	// TODO: in the future, if an FSM-based lexer is used, this should go
	//       back to being the responsibility of the lexer
	else if (cur_type == TOK_IDENIFIER) {
		if (!strcmp(*buf, "return")) {
			/* Reset buffer here to allow for new input */
			free(*buf);
			*buf = (char*) calloc(LEXER_BUF_INCR, sizeof(char));
			// TODO: consider a common section to if any of the above conditions passed
			return tk_append_ll(head, tk_new(TOK_RETURN, 0, ""));
		} else if (!strcmp(*buf, "fn")) {
			/* Reset buffer here to allow for new input */
			free(*buf);
			*buf = (char*) calloc(LEXER_BUF_INCR, sizeof(char));
			return tk_append_ll(head, tk_new(TOK_FN, 0, ""));
		}
	}
	return tk_append_ll(head, tk_new(cur_type, num, *buf));
}

/* Reset the buffer for new input */
void
_lex_reset_buf(tk_type *cur_type, int *buf_len, int *buf_pos, char* *buf)
{
	*cur_type = TOK_NULL;
	*buf_len = LEXER_BUF_INCR;
	*buf_pos = 0;
	free(*buf);
	*buf = (char*) calloc(*buf_len, sizeof(char));
}

int
lex_indent_lvl(char* src)
{
	char* res = src;
	// TODO: spaces aren't the only whitespace. this needs to be more robust
	while (*res == ' ') res++; /* Increment indent lvl per whitespace */
	return (int) (res - src); /* subtract the pointers to obtain indent lvl */
}

// TODO: This works, but a FSM would be far more efficient
token*
lex(char* src)
{
	token *res = NULL;

	/* Prepare the buffer */
	tk_type cur_type = TOK_NULL;
	int buf_len = LEXER_BUF_INCR;
	int buf_pos = 0;
	char* buf = (char*) calloc(buf_len, sizeof(char));

	for (; *src != '\0'; src++) {
		/*
		 * Make sure the buffer has enough space to read the following
		 * token
		*/
		// TODO: would it be more efficient to keep changing the buffer
		//       increment to the biggest token length? If we see e.g. a
		//       super long identifier, what are the odds we won't see
		//       it again?
		if (buf_pos >= buf_len - 1) {
			buf_len += LEXER_BUF_INCR;
			buf = (char*) reallocarray(buf, buf_len, sizeof(char));
		}

		/* Is this a number or an identifier? */
		if ((*src >= '0' && *src <= '9') || *src == '.') {
			/* Keep consuming if already predicting a valid type */
			if (cur_type == TOK_NUM || cur_type == TOK_IDENIFIER)
				buf[buf_pos++] = *src;
			/* 
			 * If current type does not allow for numbers, commit
			 * prior token and start looking for a number: We can
			 * assume new token is a number as identifiers cannot
			 * start with numbers
			 */
			else {
				res = _lex_new_tk(res, cur_type, &buf);
				_lex_reset_buf(&cur_type, &buf_len, &buf_pos,
					       &buf);
				cur_type = TOK_NUM; /* Predict a number */
				buf[buf_pos++] = *src;
			}
		/* Recognizing identifiers */
		} else if  ((*src >= 'A' && *src <= 'Z') || 
			    (*src >= 'a' && *src <= 'z')) {
			/* If already predicting an identifier, keep consuming */
			if (cur_type == TOK_IDENIFIER) buf[buf_pos++] = *src;
			/* 
			 * If not already in an identifier, commit the prior
			 * token and start looking for an identifier
			 */
			else {
				res = _lex_new_tk(res, cur_type, &buf);
				_lex_reset_buf(&cur_type, &buf_len, &buf_pos,
					       &buf);
				cur_type = TOK_IDENIFIER; /* Predict an identifier */
				buf[buf_pos++] = *src;
			}
		/*
		 * Recognizing single-character operators:
		 * Upon seeing a character that is sufficient to be a standalone
		 * operator, commit the token prior and also add the operator.
		 *
		 * For an example, see immediately below:
		 */
		} else if (*src == '=') {
			/* Commit the token before */
			res = _lex_new_tk(res, cur_type, &buf);
			/* Commit the current operator */
			res = _lex_new_tk(res, TOK_ASSIGNMENT, &buf);
			/* Reset the buffer for new input */
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
		/* Otherwise: */
		} else {
			// TODO: this should really throw a warning at least
			printf("Lexer: Unknown character, ignoring\n");
			res = _lex_new_tk(res, cur_type, &buf);
			_lex_reset_buf(&cur_type, &buf_len, &buf_pos, &buf);
		}
	}

	/*
	 * If, by the end of our input, we still have characters and we know it
	 * isn't recognized as an operator, try recognizing it as an identifier
	 * or keyword
	 */
	if (buf_pos != 0) res = _lex_new_tk(res, cur_type, &buf);
	free(buf);

	return res;
}
