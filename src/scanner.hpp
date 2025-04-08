#pragma once

#include "common.hpp"
#include "token.hpp"
#include "token_type.hpp"

class Scanner {
    std::string src;
    std::vector<Token> tokens;

    static std::unordered_map<std::string, TokenType> keywords;

    int start = 0;
    int current = 0;
    int line = 1;

    bool is_at_end();
    void scan_token();
    char advance();
    void add_token(TokenType type);
    void add_token(TokenType type, Literal literal);
    bool match(char expected);
    char peek();
    char peek_next();
    void string();
    void number();
    void identifier();

public:
    Scanner(std::string src)
        : src(src) {};
    std::vector<Token> scan_tokens();
};
