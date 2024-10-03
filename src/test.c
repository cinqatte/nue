#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    TYPE_EOF,
    TYPE_BOOL_LITERAL,
    TYPE_CHAR_LITERAL,
    TYPE_INT_LITERAL,
    TYPE_FLOAT_LITERAL,
    TYPE_STRING_LITERAL,
    TYPE_ADD,
    TYPE_SUB,
    TYPE_MUL,
    TYPE_DIV,
    TYPE_MOD,
    TYPE_ASSIGN,
    TYPE_OR,
    TYPE_NOT,
    TYPE_AND,
    TYPE_LESS_THAN,
    TYPE_GREATER_THAN,
    TYPE_NOT_EQUAL,
    TYPE_LESS_THAN_EQUAL,
    TYPE_GREATER_THAN_EQUAL,
    TYPE_BIT_OR,
    TYPE_BIT_NOT,
    TYPE_BIT_AND,
    TYPE_BIT_XOR,
    TYPE_BIT_LEFT_SHIFT,
    TYPE_BIT_RIGHT_SHIFT,
    TYPE_LEFT_PARENTHESIS,
    TYPE_RIGHT_PARENTHESIS,
    TYPE_LEFT_BRACKET,
    TYPE_RIGHT_BRACKET,
    TYPE_LEFT_BRACE,
    TYPE_RIGHT_BRACE,
    TYPE_PERIOD,
    TYPE_COMMA,
    TYPE_COLON,
    TYPE_SEMI,
    TYPE_VAR,
    TYPE_LET,
    TYPE_CONST,
    TYPE_VOID,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_ANY,
    TYPE_ENUM,
    TYPE_STRUCT,
    TYPE_FUN,
    TYPE_IF,
    TYPE_ELIF,
    TYPE_ELSE,
    TYPE_SWITCH,
    TYPE_CASE,
    TYPE_DEFAULT,
    TYPE_FOR,
    TYPE_WHILE,
    TYPE_DO,
    TYPE_CONTINUE,
    TYPE_BREAK,
    TYPE_RETURN,
    TYPE_IDENTIFIER,
    TYPE_ERROR,

	TYPE_OPERATOR,
	TYPE_DELIMITER
} Type;

typedef enum {
    VALUE_BOOL,
    VALUE_CHAR,
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_STRING
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool bool_val;
        char char_val;
        int64_t int_val;
        double float_val;
        char* string_val;
    } value;
} Value;

typedef struct {
    Type type;
    Value value;
} Token;

Token* token_new(Type type, Value value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token;
}

void token_free(Token* token) {
    if (token->value.type == VALUE_STRING) {
        free(token->value.value.string_val);
    }
    free(token);
}

const char* token_type_to_string(Type type) {
    switch (type) {
        case TYPE_EOF: return "EOF";
        case TYPE_BOOL_LITERAL: return "BOOL_LITERAL";
        case TYPE_CHAR_LITERAL: return "CHAR_LITERAL";
        case TYPE_INT_LITERAL: return "INT_LITERAL";
        case TYPE_FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TYPE_STRING_LITERAL: return "STRING_LITERAL";
        case TYPE_ADD: return "ADD";
        case TYPE_SUB: return "SUB";
        case TYPE_MUL: return "MUL";
        case TYPE_DIV: return "DIV";
        case TYPE_MOD: return "MOD";
        case TYPE_ASSIGN: return "ASSIGN";
        case TYPE_OR: return "OR";
        case TYPE_NOT: return "NOT";
        case TYPE_AND: return "AND";
        case TYPE_LESS_THAN: return "LESS_THAN";
        case TYPE_GREATER_THAN: return "GREATER_THAN";
        case TYPE_NOT_EQUAL: return "NOT_EQUAL";
        case TYPE_LESS_THAN_EQUAL: return "LESS_THAN_EQUAL";
        case TYPE_GREATER_THAN_EQUAL: return "GREATER_THAN_EQUAL";
        case TYPE_BIT_OR: return "BIT_OR";
        case TYPE_BIT_NOT: return "BIT_NOT";
        case TYPE_BIT_AND: return "BIT_AND";
        case TYPE_BIT_XOR: return "BIT_XOR";
        case TYPE_BIT_LEFT_SHIFT: return "BIT_LEFT_SHIFT";
        case TYPE_BIT_RIGHT_SHIFT: return "BIT_RIGHT_SHIFT";
        case TYPE_LEFT_PARENTHESIS: return "LEFT_PARENTHESIS";
        case TYPE_RIGHT_PARENTHESIS: return "RIGHT_PARENTHESIS";
        case TYPE_LEFT_BRACKET: return "LEFT_BRACKET";
        case TYPE_RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TYPE_LEFT_BRACE: return "LEFT_BRACE";
        case TYPE_RIGHT_BRACE: return "RIGHT_BRACE";
        case TYPE_PERIOD: return "PERIOD";
        case TYPE_COMMA: return "COMMA";
        case TYPE_COLON: return "COLON";
        case TYPE_SEMI: return "SEMI";
        case TYPE_VAR: return "VAR";
        case TYPE_LET: return "LET";
        case TYPE_CONST: return "CONST";
        case TYPE_VOID: return "VOID";
        case TYPE_BOOL: return "BOOL";
        case TYPE_CHAR: return "CHAR";
        case TYPE_INT: return "INT";
        case TYPE_FLOAT: return "FLOAT";
        case TYPE_STRING: return "STRING";
        case TYPE_ANY: return "ANY";
        case TYPE_ENUM: return "ENUM";
        case TYPE_STRUCT: return "STRUCT";
        case TYPE_FUN: return "FUN";
        case TYPE_IF: return "IF";
        case TYPE_ELIF: return "ELIF";
        case TYPE_ELSE: return "ELSE";
        case TYPE_SWITCH: return "SWITCH";
        case TYPE_CASE: return "CASE";
        case TYPE_DEFAULT: return "DEFAULT";
        case TYPE_FOR: return "FOR";
        case TYPE_WHILE: return "WHILE";
        case TYPE_DO: return "DO";
        case TYPE_CONTINUE: return "CONTINUE";
        case TYPE_BREAK: return "BREAK";
        case TYPE_RETURN: return "RETURN";
        case TYPE_IDENTIFIER: return "IDENTIFIER";
        case TYPE_ERROR: return "ERROR";
		case TYPE_OPERATOR: return "TYPE_OPERATOR";
		case TYPE_DELIMITER: return "TYPE_DELIMITER";
        default: return "UNKNOWN";
    }
}

void print_token(Token* token) {
    printf("Token type: %s", token_type_to_string(token->type));
    if (token->type == TYPE_INT_LITERAL) {
        printf(", Value: %lld", token->value.value.int_val);
    } else if (token->type == TYPE_FLOAT_LITERAL) {
        printf(", Value: %f", token->value.value.float_val);
    } else if (token->type == TYPE_BOOL_LITERAL) {
        printf(", Value: %s", token->value.value.bool_val ? "true" : "false");
    } else if (token->type == TYPE_CHAR_LITERAL) {
        printf(", Value: '%c'", token->value.value.char_val);
    } else if (token->type == TYPE_STRING_LITERAL || token->type == TYPE_IDENTIFIER || token->type == TYPE_ERROR) {
        printf(", Value: \"%s\"", token->value.value.string_val);
    }
    printf("\n");
}

typedef struct {
    char* code;
    char* path;
    char current;
    int index;
    int line;
    int column;
} Lexer;

Lexer* lexer_new(char* code, char* path) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->code = code;
    lexer->path = path;
    lexer->current = code[0];
    lexer->index = 0;
    lexer->line = 1;
    lexer->column = 1;
    return lexer;
}

void lexer_advance(Lexer* lexer) {
    if (lexer->current != '\0' && lexer->index < strlen(lexer->code)) {
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

void lexer_skip_whitespace(Lexer* lexer) {
    while (isspace(lexer->current)) {
        lexer_advance(lexer);
    }
}

void lexer_set_error(Lexer * lexer) {
    lexer->current = '\0';
}

bool lexer_is_eof(Lexer* lexer) {
    return lexer->current == '\0' || lexer->index >= strlen(lexer->code);
}

Token* lexer_get_token(Lexer* lexer);

bool is_operator_char(char ch) {
    return strchr("+-*/%=&|!<>^~", ch) != NULL;
}

bool is_delimiter_char(char ch) {
    return strchr("()[]{}.,:;", ch) != NULL;
}

Token* lexer_get_token_number(Lexer* lexer) {
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

    char* number = strndup(&lexer->code[start], lexer->index - start);

    Token* token;
    if (strchr(number, '.') || strchr(number, 'e') || strchr(number, 'E')) {
        char* end;
        double value = strtod(number, &end);
        token = token_new(TYPE_FLOAT_LITERAL, (Value){.type = VALUE_FLOAT, .value.float_val = value});
    } else {
        int64_t value = strtoll(number, NULL, 10);
        token = token_new(TYPE_INT_LITERAL, (Value){.type = VALUE_INT, .value.int_val = value});
    }

    free(number);
    return token;
}

Token* lexer_get_token_identifier(Lexer* lexer) {
    int start = lexer->index;
    while (isalnum(lexer->current) || lexer->current == '_') {
        lexer_advance(lexer);
    }

    char* identifier = strndup(&lexer->code[start], lexer->index - start);
    Token* token = token_new(TYPE_IDENTIFIER, (Value){.type = VALUE_STRING, .value.string_val = identifier});
    return token;
}

Token* lexer_get_token_operator(Lexer* lexer) {
    int start = lexer->index;
    while (is_operator_char(lexer->current)) {
        lexer_advance(lexer);
    }

    char* operator= strndup(&lexer->code[start], lexer->index - start);
    Token* token = token_new(TYPE_OPERATOR, (Value){.type = VALUE_STRING, .value.string_val = operator});
    return token;
}

Token* lexer_get_token_delimiter(Lexer* lexer) {
    char delimiter = lexer->current;
    lexer_advance(lexer);
    Token* token = token_new(TYPE_DELIMITER, (Value){.type = VALUE_CHAR, .value.char_val = delimiter});
    return token;
}

Token* lexer_get_token_char(Lexer* lexer) {
    lexer_advance(lexer);
    char ch = lexer->current;
    lexer_advance(lexer);
    if (lexer->current != '\'') {
        lexer_set_error(lexer);
        char* error_msg = (char*)malloc(256);
        snprintf(error_msg, 256, "%s:%d:%d: unterminated char literal", lexer->path, lexer->line, lexer->column);
        return token_new(TYPE_ERROR, (Value){.type = VALUE_STRING, .value.string_val = error_msg});
    }
    lexer_advance(lexer);
    return token_new(TYPE_CHAR_LITERAL, (Value){.type = VALUE_CHAR, .value.char_val = ch});
}

Token* lexer_get_token_string(Lexer* lexer) {
    lexer_advance(lexer);
    int start = lexer->index;
    while (lexer->current != '"' && !lexer_is_eof(lexer)) {
        lexer_advance(lexer);
    }
    char* string_content = strndup(&lexer->code[start], lexer->index - start);
    if (lexer_is_eof(lexer)) {
        lexer_set_error(lexer);
        char* error_msg = (char*)malloc(256);
        snprintf(error_msg, 256, "%s:%d:%d: unterminated string literal", lexer->path, lexer->line, lexer->column);
        free(string_content);
        return token_new(TYPE_ERROR, (Value){.type = VALUE_STRING, .value.string_val = error_msg});
    }
    lexer_advance(lexer);
    return token_new(TYPE_STRING_LITERAL, (Value){.type = VALUE_STRING, .value.string_val = string_content});
}

Token* lexer_get_token(Lexer* lexer) {
    if (lexer_is_eof(lexer)) {
        Value value = {.type = VALUE_CHAR, .value.char_val = '\0'};
        return token_new(TYPE_EOF, value);
    }

    lexer_skip_whitespace(lexer);

    if (isdigit(lexer->current)) {
        return lexer_get_token_number(lexer);
    }

    if (isalpha(lexer->current) || lexer->current == '_') {
        return lexer_get_token_identifier(lexer);
    }

    if (is_operator_char(lexer->current)) {
        return lexer_get_token_operator(lexer);
    }

    if (is_delimiter_char(lexer->current)) {
        return lexer_get_token_delimiter(lexer);
    }

    if (lexer->current == '\'') {
        return lexer_get_token_char(lexer);
    }

    if (lexer->current == '"') {
        return lexer_get_token_string(lexer);
    }

    char ch = lexer->current;
    lexer_set_error(lexer);
    char* error_msg = (char*)malloc(256);
    snprintf(error_msg, 256, "%s:%d:%d: unknown character '%c'", lexer->path, lexer->line, lexer->column, ch);
    return token_new(TYPE_ERROR, (Value){.type = VALUE_STRING, .value.string_val = error_msg});
}

int main() {
    // Example usage
    char* code = "int main() { return \"hello\"; }";
    char* path = "example.c";
    Lexer* lexer = lexer_new(code, path);

    Token* token;
    while ((token = lexer_get_token(lexer))->type != TYPE_EOF) {
        print_token(token);
        token_free(token);
    }
    token_free(token); // Free the EOF token

    // Free the lexer after use
    free(lexer);

    return 0;
}
