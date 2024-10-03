#pragma once

#ifndef NUE_TOKEN_H
#define NUE_TOKEN_H

typedef enum TokenType {
    TT_LITERAL_EOF, TT_LITERAL_BOOL, TT_LITERAL_CHAR,
    TT_LITERAL_INT, TT_LITERAL_FLOAT, TT_LITERAL_STRING,
    
    TT_OP_ADD, TT_OP_SUB, TT_OP_MUL,
    TT_OP_DIV, TT_OP_MOD,

    TT_OP_ASSIGNMENT,

    TT_OP_OR, TT_OP_NOT, TT_OP_AND,

    TT_OP_LT, TT_OP_GT, TT_OP_EQ,
    TT_OP_NEQ, TT_OP_LTE, TT_OP_GTE,

    TT_OP_BIT_OR, TT_OP_BIT_NOT, TT_OP_BIT_AND,
    TT_OP_BIT_XOR, TT_OP_BIT_LT, TT_OP_BIT_RT,

    TT_DEL_LPN, TT_DEL_RPN, TT_DEL_LBT,
    TT_DEL_RBT, TT_DEL_LBC, TT_DEL_RBC,
    TT_DEL_PRD, TT_DEL_CMA, TT_DEL_CLN,
    TT_DEL_SMI,

    TT_KEY_BOOL, TT_KEY_CHAR, TT_KEY_SHORT,
    TT_KEY_INT, TT_KEY_LONG, TT_KEY_FLOAT,
    TT_KEY_DOUBLE, TT_KEY_STRUCT, TT_KEY_FUN,

    TT_KEY_IF, TT_KEY_ELIF, TT_KEY_ELSE,
    TT_KEY_FOR, TT_KEY_WHILE, TT_KEY_DO,
    TT_KEY_SWITCH, TT_KEY_CASE, TT_KEY_DEFAULT,
    TT_KEY_BREAK, TT_KEY_CONTINUE, TT_KEY_RETURN,

    TT_IDENTIFIER
} TokenType;

typedef enum TokenValueType {
    TT_VAL_EOF = 100, TT_VAL_BOOL, TT_VAL_CHAR,
    TT_VAL_INT, TT_VAL_FLOAT, TT_VAL_STRING
} TokenValueType;

typedef struct TokenValue {
    TokenValueType type;
    union  {
        unsigned char boolean;
        char character;
        long integer;
        double floating_point;
        char * string;
    } value;
} TokenValue;

typedef struct Token {
    TokenType type;
    TokenValue value;
} Token;

Token token_new(TokenType type, TokenValue value);
TokenType token_get_type(Token * token);
TokenValue token_get_value(Token * token);
const char * token_type_to_string(TokenType type);

#endif // NUE_TOKEN_H
