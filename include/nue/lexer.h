#pragma once

#ifndef NUE_LEXER_H
#define NUE_LEXER_H

#include "nue/token.h"

typedef struct {
    char * code;
    char * path;
    char current;
	int length;
    int index;
    int line;
    int column;
} Lexer;

Lexer lexer_new(char * code, int length, char * path);
void lexer_advance(Lexer * lexer);
void lexer_skip_whitespace(Lexer * lexer);
void lexer_set_error(Lexer * lexer);
int lexer_is_eof(Lexer * lexer);
int is_operator_char(char ch);
int is_delimiter_char(char ch);
Token lexer_get_token_number(Lexer * lexer)

#endif // NUE_LEXER_H
