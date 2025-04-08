#pragma once

/* Auto generated using helper method generate_ast() for the CFG
Expression: Expr expression
Print: Expr expression
Var: Token name, Expr initializer
*/
#include "expr.hpp"

class Expression;
class Print;
class Var;

using Stmt = std::variant<Expression, Print, Var>;

class Expression{
public:
Expression(std::unique_ptr<Expr>&& expression) : expression(std::move(expression))  {}

std::unique_ptr<Expr> expression;
};

class Print{
public:
Print(std::unique_ptr<Expr>&& expression) : expression(std::move(expression))  {}

std::unique_ptr<Expr> expression;
};

class Var{
public:
Var(Token name, std::unique_ptr<Expr>&& initializer) : name(name), initializer(std::move(initializer))  {}

Token name;
std::unique_ptr<Expr> initializer;
};

