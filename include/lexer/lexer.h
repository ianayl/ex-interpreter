#ifndef LEXER_H
#define LEXER_H

/* Lexer -- header file */

#include "lexer/tokens.h"

/* Increments to extend the buffer by */
#define LEXER_BUF_INCR 4
// TODO do some investigation and enlargen this later

/**
 * Helper function to figure out the indentation level of the line being lexed
 *
 * @param src the string to count indentation level of
 * @return number of white spaces (indentation level) of src
 */
int lex_indent_lvl(char* src);

/**
 * Lex string src into a token list
 *
 * @param src the string to lex
 * @return a tokenlist comrpised of the tokens in src
 */
token* lex(char* src);

#endif
