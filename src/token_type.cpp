#include "token_type.hpp"

std::ostream& operator<<(std::ostream& strm, TokenType tt)
{
    switch (tt) {
    case LEFT_PAREN:
        strm << "LEFT_PAREN";
        break;
    case WHILE:
        strm << "WHILE";
        break;
    case VAR:
        strm << "VAR";
        break;
    case TRUE:
        strm << "TRUE";
        break;
    case THIS:
        strm << "THIS";
        break;
    case SUPER:
        strm << "SUPER";
        break;
    case RETURN:
        strm << "RETURN";
        break;
    case PRINT:
        strm << "PRINT";
        break;
    case OR:
        strm << "OR";
        break;
    case NIL:
        strm << "NIL";
        break;
    case IF:
        strm << "IF";
        break;
    case FOR:
        strm << "FOR";
        break;
    case FUN:
        strm << "FUN";
        break;
    case FALSE:
        strm << "FALSE";
        break;
    case ELSE:
        strm << "ELSE";
        break;
    case CLASS:
        strm << "CLASS";
        break;
    case AND:
        strm << "AND";
        break;
    case NUMBER:
        strm << "NUMBER";
        break;
    case STRING:
        strm << "STRING";
        break;
    case IDENTIFIER:
        strm << "IDENTIFIER";
        break;
    case LESS_EQUAL:
        strm << "LESS_EQUAL";
        break;
    case LESS:
        strm << "LESS";
        break;
    case GREATER_EQUAL:
        strm << "GREATER_EQUAL";
        break;
    case GREATER:
        strm << "GREATER";
        break;
    case EQUAL_EQUAL:
        strm << "EQUAL_EQUAL";
        break;
    case EQUAL:
        strm << "EQUAL";
        break;
    case BANG_EQUAL:
        strm << "BANG_EQUAL";
        break;
    case BANG:
        strm << "BANG";
        break;
    case STAR:
        strm << "STAR";
        break;
    case SLASH:
        strm << "SLASH";
        break;
    case SEMICOLON:
        strm << "SEMICOLON";
        break;
    case PLUS:
        strm << "PLUS";
        break;
    case MINUS:
        strm << "MINUS";
        break;
    case DOT:
        strm << "DOT";
        break;
    case COMMA:
        strm << "COMMA";
        break;
    case RIGHT_BRACE:
        strm << "RIGHT_BRACE";
        break;
    case LEFT_BRACE:
        strm << "LEFT_BRACE";
        break;
    case RIGHT_PAREN:
        strm << "RIGHT_PAREN";
        break;
    case TOKEN_EOF:
        strm << "TOKEN_EOF";
        break;
    }

    return strm;
}
