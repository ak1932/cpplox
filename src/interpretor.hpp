#pragma once

#include "common.hpp"
#include "expr.hpp"
#include "stmt.hpp"

class Interpretor {
    class RuntimeError : public std::runtime_error {
        public:
            Token token;
            RuntimeError(Token token, std::string message) : token(token), std::runtime_error(message) {}
    };

    Literal evaluate(Expr* expr);
    std::string stringify_literal(Literal& lit);
    void execute(Stmt* stmt);
    void interpret(std::vector<Stmt>& statements);
    bool is_truthy(Literal lit);
    bool is_equal(Literal left, Literal right);

public:
    Literal operator()(Binary& expr);
    Literal operator()(Grouping& expr);
    Literal operator()(Lit& expr);
    Literal operator()(Unary& expr);
    void operator()(Print& expr);
    void operator()(Expression& expr);

    // Literal visitBinaryExpr(Binary& expr) override;
    // Literal visitGroupingExpr(Grouping& expr) override;
    // Literal visitLitExpr(Lit& expr) override;
    // Literal visitUnaryExpr(Unary& expr) override;
    friend class Cpplox;
};
