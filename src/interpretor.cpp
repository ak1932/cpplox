#include "interpretor.hpp"
#include "cpplox.hpp"

Literal Interpretor::evaluate(Expr* expr)
{
    return std::visit(Interpretor {}, *expr);
}

std::string Interpretor::stringify_literal(Literal& lit)
{
    if (std::holds_alternative<double>(lit)) {
        return std::to_string(std::get<double>(lit));
    } else if (std::holds_alternative<std::string>(lit)) {
        return std::get<std::string>(lit);
    } else if (std::holds_alternative<bool>(lit)) {
        return std::get<bool>(lit) ? "true" : "false";
    } else {
        throw RuntimeError(Token(NIL, "", "", 6969), "Literal type not handeled");
    }
}
void Interpretor::interpret(std::vector<Stmt>& stmts)
{
    try {
        for(auto& stmt: stmts) {
            execute(&stmt);
        }
    } catch (RuntimeError error) {
        Cpplox::runtime_error(error);
    }
}

void Interpretor::execute(Stmt* stmt) {
    std::visit(Interpretor{}, *stmt);
}

// Literal Interpretor::print(std::unique_ptr<Expr>& expr)
// {
//     return expr->accept(*this);
// }
//

void Interpretor::operator()(Expression& expr)
{
    evaluate(expr.expression.get());
}

void Interpretor::operator()(Print& print)
{
    Literal val = evaluate(print.expression.get());
    std::cout << stringify_literal(val) << "\n";
}

Literal Interpretor::operator()(Binary& expr)
{
    Literal left = evaluate(expr.left.get());
    Literal right = evaluate(expr.right.get());
    switch (expr.oper.type) {
    case STAR: {
        return std::get<double>(left) * std::get<double>(right);
        break;
    }
    case MINUS: {
        return std::get<double>(left) - std::get<double>(right);
        break;
    }
    case SLASH: {
        return std::get<double>(left) / std::get<double>(right);
        break;
    }
    case PLUS: {
        if (std::holds_alternative<double>(left) and std::holds_alternative<double>(right)) {
            return std::get<double>(left) + std::get<double>(right);
        } else if (std::holds_alternative<std::string>(left) and std::holds_alternative<std::string>(right)) {
            return std::get<std::string>(left) + std::get<std::string>(right);
        } else {
            throw RuntimeError(expr.oper, "Operands must be same type for PLUS");
        }
        break;
    }
    case GREATER: {
        return std::get<double>(left) > std::get<double>(right);
        break;
    }
    case GREATER_EQUAL: {
        return std::get<double>(left) >= std::get<double>(right);
        break;
    }
    case LESS: {
        return std::get<double>(left) < std::get<double>(right);
        break;
    }
    case LESS_EQUAL: {
        return std::get<double>(left) <= std::get<double>(right);
        break;
    }
    case BANG_EQUAL: {
        return !is_equal(left, right);
        break;
    }
    case EQUAL_EQUAL: {
        return is_equal(left, right);
        break;
    }
    default: {
        throw RuntimeError(expr.oper, "operator not handled for binary");
        break;
    }
    }
}

Literal Interpretor::operator()(Grouping& expr)
{
    return evaluate(expr.expression.get());
}

Literal Interpretor::operator()(Lit& expr)
{
    if (std::holds_alternative<double>(expr.value)) {
        return std::get<double>(expr.value);
    } else if (std::holds_alternative<std::string>(expr.value)) {
        return std::get<std::string>(expr.value);
    } else if (std::holds_alternative<bool>(expr.value)) {
        return std::get<bool>(expr.value);
    } else {
        throw RuntimeError(Token(NIL, "", "", 6969), "Literal type not handeled");
    }
}

Literal Interpretor::operator()(Unary& expr)
{
    Literal value = evaluate(expr.right.get());

    switch (expr.oper.type) {
    case BANG: {
        return !is_truthy(value);
        break;
    }
    case MINUS: {
        return -std::get<double>(value);
        break;
    }
    default: {
        throw RuntimeError(expr.oper, "operator not handled for unary");
        break;
    }
    }
}

bool Interpretor::is_truthy(Literal literal)
{
    if (std::holds_alternative<double>(literal)) {
        return std::get<double>(literal);
    } else if (std::holds_alternative<std::string>(literal)) {
        return std::get<std::string>(literal).size();
    } else if (std::holds_alternative<bool>(literal)) {
        return std::get<bool>(literal);
    } else {
        throw RuntimeError(Token(NIL, "", "", 6969), "values not handled for truthy");
    }
}

bool Interpretor::is_equal(Literal left, Literal right)
{
    if (std::holds_alternative<double>(left) and std::holds_alternative<double>(right)) {
        return std::get<double>(left) == std::get<double>(right);
    } else if (std::holds_alternative<std::string>(left) and std::holds_alternative<std::string>(right)) {
        return std::get<std::string>(left) == std::get<std::string>(right);
    } else if (std::holds_alternative<bool>(left) and std::holds_alternative<bool>(right)) {
        return std::get<bool>(left) == std::get<bool>(right);
    } else {
        throw RuntimeError(Token(NIL, "", "", 6969), "values not handled for equal");
    }
}
