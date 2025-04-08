#pragma once

/* Auto generated using helper method generate_ast() for the CFG
Binary: Expr left, Token oper, Expr right
Grouping: Expr expression
Lit: Literal value
Unary: Token oper, Expr right
Variable: Token name
*/
#include "token.hpp"

class Binary;
class Grouping;
class Lit;
class Unary;
class Variable;

using Expr = std::variant<Binary, Grouping, Lit, Unary, Variable>;

class Binary{
public:
Binary(std::unique_ptr<Expr>&& left, Token oper, std::unique_ptr<Expr>&& right) : left(std::move(left)), oper(oper), right(std::move(right))  {}

std::unique_ptr<Expr> left;
Token oper;
std::unique_ptr<Expr> right;
};

class Grouping{
public:
Grouping(std::unique_ptr<Expr>&& expression) : expression(std::move(expression))  {}

std::unique_ptr<Expr> expression;
};

class Lit{
public:
Lit(Literal value) : value(value)  {}

Literal value;
};

class Unary{
public:
Unary(Token oper, std::unique_ptr<Expr>&& right) : oper(oper), right(std::move(right))  {}

Token oper;
std::unique_ptr<Expr> right;
};

class Variable{
public:
Variable(Token name) : name(name)  {}

Token name;
};

