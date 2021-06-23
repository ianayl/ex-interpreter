#ifndef LEXER_H
#define LEXER_H

#include "lexer/tokens.h"

#define LEXER_BUF_INCR 4

token* lex (char* src);

#endif
