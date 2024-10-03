#include "nue/lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

Lexer lexer_new(char * code, int length, char * path) {
	return (Lexer) {.code = code, .length = length, .path = path, .current = code[0], .index = 0, .line = 1, .column = 1};
}

void lexer_advance(Lexer * lexer) {
    if (lexer->current != '\0' && lexer->index < lexer->length) {
        if (lexer->current == '\n') {
            lexer->line++;
            lexer->column = 0;
        } else {
            lexer->column++;
        }
        lexer->index++;
        lexer->current = lexer->code[lexer->index];
    } else {
        lexer->current = '\0';
    }
}

void lexer_skip_whitespace(Lexer * lexer) {
    while (isspace(lexer->current)) {
        lexer_advance(lexer);
    }
}

void lexer_set_error(Lexer * lexer) {
    lexer->current = '\0';
}

int lexer_is_eof(Lexer * lexer) {
    return lexer->current == '\0' || lexer->index >= lexer->length;
}

int is_operator_char(char ch) {
    return strchr("+-*/%=&|!<>^~", ch) != NULL;
}

int is_delimiter_char(char ch) {
    return strchr("()[]{}.,:;", ch) != NULL;
}


Token lexer_get_token_number(Lexer * lexer) {
    int start = lexer->index;
    while (isdigit(lexer->current)) {
        lexer_advance(lexer);
    }

    if (lexer->current == '.') {
        lexer_advance(lexer);
        while (isdigit(lexer->current)) {
            lexer_advance(lexer);
        }
    }

    if (lexer->current == 'e' || lexer->current == 'E') {
        lexer_advance(lexer);
        if (lexer->current == '+' || lexer->current == '-') {
            lexer_advance(lexer);
        }
        while (isdigit(lexer->current)) {
            lexer_advance(lexer);
        }
    }

    char * number = strndup(&lexer->code[start], lexer->index - start);

    Token token;
    if (strchr(number, '.') || strchr(number, 'e') || strchr(number, 'E')) {
        char * end;
        double value = strtod(number, &end);
        token = token_new(TT_LITERAL_FLOAT, (TokenValue){.type = TT_VAL_FLOAT, .value.floating_point = value});
    } else {
        long value = strtoll(number, NULL, 10);
        token = token_new(TT_LITERAL_INT, (TokenValue){.type = TT_VAL_INT, .value.integer = value});
    }

    free(number);
    return token;
}
