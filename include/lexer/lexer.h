#ifndef LEXER_H
#define LEXER_H

#include "lexer/tokens.h"

#define LEXER_BUF_INCR 4

int lex_indent_lvl(char* src);
token* lex(char* src);

#endif
