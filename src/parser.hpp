#pragma once

/*
parsing for =>

expression => equality ;
equality => comparison ( ( "!=" | "==" ) comparison )* ;
comparison => term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term => factor ( ( "-" | "+" ) factor )* ;
factor=> unary ( ( "/" | "*" ) unary )* ;
unary => ( "!" | "-" ) unary
            | primary ;
primary => NUMBER | STRING | "true" | "false" | "nil"
            | "(" expression ")" ;
 */

#include "expr.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include "stmt.hpp"
#include <exception>


class Parser {
    class ParseError : public std::exception { };
    int current = 0;

    Expr expression();
    Expr equality();
    Expr comparision();
    Expr term();
    Expr factor();
    Expr unary();
    Expr primary();

    bool match(const std::vector<TokenType>&& types);
    bool check(TokenType type);
    bool is_at_end();

    std::vector<Token> tokens;
    Token advance();
    Token peek();
    Token previous();
    Token consume(TokenType token, std::string msg);

    ParseError error(Token token, std::string msg);

    Stmt statement();
    Stmt print_statement();
    Stmt expression_statement();
    Stmt declaration();
    Stmt var_declaration();
    std::vector<Stmt> parse();

    void synchronize();

    public:
    Parser(std::vector<Token> tokens) : tokens(tokens) {}

    friend class Cpplox;
};
