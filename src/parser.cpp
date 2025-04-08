#include "parser.hpp"
#include "cpplox.hpp"
#include "token_type.hpp"
#include <memory>

std::vector<Stmt> Parser::parse()
{
    std::vector<Stmt> stmts;
    while (!is_at_end()) {
        stmts.push_back(declaration());
    }

    return stmts;
}

Stmt Parser::declaration()
{
    try {
        if (match({ VAR }))
            return var_declaration();

        return statement();
    } catch (ParseError error) {
        synchronize();
        return Null();
    }
}

Stmt Parser::var_declaration()
{
    Token name = consume(IDENTIFIER, "Expect variable name.");
    Expr initializer = Null();
    if (match({ EQUAL })) {
        initializer = expression();
    }
    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return Var(name, std::make_unique<Expr>(std::move(initializer)));
}

Stmt Parser::statement()
{
    if (match({ PRINT }))
        return print_statement();

    return expression_statement();
}

Stmt Parser::print_statement()
{
    Expr expr = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return Print(std::make_unique<Expr>(std::move(expr)));
}

Stmt Parser::expression_statement()
{
    Expr expr = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return Expression(std::make_unique<Expr>(std::move(expr)));
}

Expr Parser::expression()
{
    return equality();
}

Expr Parser::equality()
{
    Expr expr = comparision();
    while (match({ BANG_EQUAL, EQUAL_EQUAL })) {
        Token oper = previous();
        Expr right = comparision();
        expr = Binary(std::make_unique<Expr>(std::move(expr)), oper, std::make_unique<Expr>(std::move(right)));
    }
    return expr;
}

Expr Parser::comparision()
{
    Expr expr = term();
    while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
        Token oper = previous();
        Expr right = term();
        expr = Binary(std::make_unique<Expr>(std::move(expr)), oper, std::make_unique<Expr>(std::move(right)));
    }

    return expr;
}

Expr Parser::term()
{
    Expr expr = factor();
    while (match({ MINUS, PLUS })) {
        Token oper = previous();
        Expr right = factor();
        expr = Binary(std::make_unique<Expr>(std::move(expr)), oper, std::make_unique<Expr>(std::move(right)));
    }
    return expr;
}

Expr Parser::factor()
{
    Expr expr = unary();
    while (match({ STAR, SLASH })) {
        Token oper = previous();
        Expr right = unary();
        expr = Binary(std::make_unique<Expr>(std::move(expr)), oper, std::make_unique<Expr>(std::move(right)));
    }
    return expr;
}

Expr Parser::unary()
{
    if (match({ BANG, MINUS })) {
        Token oper = previous();
        Expr right = unary();
        return Expr(Unary(oper, std::make_unique<Expr>(std::move(right))));
    }

    return primary();
}

Expr Parser::primary()
{
    if (match({ FALSE }))
        return Expr(Lit(bool(false)));
    if (match({ TRUE }))
        return Expr(Lit(bool(true)));
    if (match({ NIL }))
        return Expr(Lit(nullptr));

    if (match({ NUMBER, STRING })) {
        return Expr(Lit(previous().literal));
    }

    if(match({IDENTIFIER})) {
        return Variable(previous());
    }

    if (match({ LEFT_PAREN })) {
        Expr expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return Expr(Grouping(std::make_unique<Expr>(std::move(expr))));
    }
    throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, std::string msg)
{
    if (check(type))
        return advance();

    throw error(peek(), msg);
}

Parser::ParseError Parser::error(Token token, std::string msg)
{
    Cpplox::error(token, msg);
    return ParseError();
}

bool Parser::match(const std::vector<TokenType>&& types)
{
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type)
{
    if (is_at_end())
        return false;
    return peek().type == type;
}

Token Parser::advance()
{
    if (!is_at_end())
        current++;

    return previous();
}

void Parser::synchronize()
{
    advance();
    while (!is_at_end()) {
        if (previous().type == SEMICOLON)
            return;
        switch (peek().type) {
        case CLASS:
        case FUN:
        case VAR:
        case FOR:
        case IF:
        case WHILE:
        case PRINT:
        case RETURN:
            return;
        default:
            Cpplox::error(peek().line, "error while synch");
        }
        advance();
    }
}

bool Parser::is_at_end()
{
    return peek().type == TOKEN_EOF;
}
Token Parser::peek()
{
    return tokens[current];
}
Token Parser::previous()
{
    return tokens[current - 1];
}
