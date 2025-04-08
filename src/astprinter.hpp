#pragma once

#include "common.hpp"
#include "expr.hpp"

class AstPrinter {
    Literal parenthesize(std::string name, const std::vector<Expr*>&& exprs);

public:
    Literal operator()(Binary& expr);
    Literal operator()(Grouping& expr);
    Literal operator()(Lit& expr);
    Literal operator()(Unary& expr);

    // Literal visitBinaryExpr(Binary& expr) override;
    // Literal visitGroupingExpr(Grouping& expr) override;
    // Literal visitLitExpr(Lit& expr) override;
    // Literal visitUnaryExpr(Unary& expr) override;
};
