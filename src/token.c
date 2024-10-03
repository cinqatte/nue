#include "nue/token.h"

Token token_new(TokenType type, TokenValue value) {
	return (Token) {.type = type, .value = value };
}

TokenType token_get_type(Token * token) {
	return token->type;
}

TokenValue token_get_value(Token * token) {
	return token->value;
}

const char * token_type_to_string(TokenType type) {
	switch (type)
	{
		case TT_OP_ADD: return "TT_OP_ADD";
		case TT_OP_SUB: return "TT_OP_SUB";
		case TT_OP_MUL: return "TT_OP_MUL";
		case TT_OP_DIV: return "TT_OP_DIV";
		case TT_OP_MOD: return "TT_OP_MOD";
		case TT_OP_ASSIGNMENT: return "TT_OP_ASSIGNMENT";
		case TT_OP_OR: return "TT_OP_OR";
		case TT_OP_NOT: return "TT_OP_NOT";
		case TT_OP_AND: return "TT_OP_AND";
		case TT_OP_LT: return "TT_OP_LT";
		case TT_OP_GT: return "TT_OP_GT";
		case TT_OP_EQ: return "TT_OP_EQ";
		case TT_OP_NEQ: return "TT_OP_NEQ";
		case TT_OP_LTE: return "TT_OP_LTE";
		case TT_OP_GTE: return "TT_OP_GTE";
		case TT_OP_BIT_OR: return "TT_OP_BIT_OR";
		case TT_OP_BIT_NOT: return "TT_OP_BIT_NOT";
		case TT_OP_BIT_AND: return "TT_OP_BIT_AND";
		case TT_OP_BIT_XOR: return "TT_OP_BIT_XOR";
		case TT_OP_BIT_LT: return "TT_OP_BIT_LT";
		case TT_OP_BIT_RT: return "TT_OP_BIT_RT";
		case TT_DEL_LPN: return "TT_DEL_LPN";
		case TT_DEL_RPN: return "TT_DEL_RPN";
		case TT_DEL_LBT: return "TT_DEL_LBT";
		case TT_DEL_RBT: return "TT_DEL_RBT";
		case TT_DEL_LBC: return "TT_DEL_LBC";
		case TT_DEL_RBC: return "TT_DEL_RBC";
		case TT_DEL_PRD: return "TT_DEL_PRD";
		case TT_DEL_CMA: return "TT_DEL_CMA";
		case TT_DEL_CLN: return "TT_DEL_CLN";
		case TT_DEL_SMI: return "TT_DEL_SMI";
		case TT_KEY_BOOL: return "TT_KEY_BOOL";
		case TT_KEY_CHAR: return "TT_KEY_CHAR";
		case TT_KEY_SHORT: return "TT_KEY_SHORT";
		case TT_KEY_INT: return "TT_KEY_INT";
		case TT_KEY_LONG: return "TT_KEY_LONG";
		case TT_KEY_FLOAT: return "TT_KEY_FLOAT";
		case TT_KEY_DOUBLE: return "TT_KEY_DOUBLE";
		case TT_KEY_STRUCT: return "TT_KEY_STRUCT";
		case TT_KEY_FUN: return "TT_KEY_FUN";
		case TT_KEY_IF: return "TT_KEY_IF";
		case TT_KEY_ELIF: return "TT_KEY_ELIF";
		case TT_KEY_ELSE: return "TT_KEY_ELSE";
		case TT_KEY_FOR: return "TT_KEY_FOR";
		case TT_KEY_WHILE: return "TT_KEY_WHILE";
		case TT_KEY_DO: return "TT_KEY_DO";
		case TT_KEY_SWITCH: return "TT_KEY_SWITCH";
		case TT_KEY_CASE: return "TT_KEY_CASE";
		case TT_KEY_DEFAULT: return "TT_KEY_DEFAULT";
		case TT_KEY_BREAK: return "TT_KEY_BREAK";
		case TT_KEY_CONTINUE: return "TT_KEY_CONTINUE";
		case TT_KEY_RETURN: return "TT_KEY_RETURN";
		case TT_IDENTIFIER: return "TT_IDENTIFIER";
		default: return "TT_UNKNOWN";
	}
}
