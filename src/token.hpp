#pragma once

#include "common.hpp"
#include "token_type.hpp"

using Literal = std::variant<double, std::string, bool>;
class Token {
public:
    std::string lexeme;
    TokenType type;
    Literal literal;
    int line;
    Token(TokenType type, std::string lexeme, Literal literal, int line) : type(type), lexeme(lexeme), literal(literal), line(line) {};
    friend std::ostream& operator<<(std::ostream& out, const Token& t);
};
