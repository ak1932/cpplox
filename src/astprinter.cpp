#include "astprinter.hpp"
#include "cpplox.hpp"

Literal AstPrinter::parenthesize(std::string name, const std::vector<Expr*>&& exprs)
{
    std::string builder;
    builder += "(" + name;
    for (auto& expr : exprs) {
        builder.append(" ");
        builder.append(std::get<std::string>(std::visit(AstPrinter {}, *expr)));
    }
    builder.append(")");
    return builder;
}

// Literal AstPrinter::print(std::unique_ptr<Expr>& expr)
// {
//     return expr->accept(*this);
// }

Literal AstPrinter::operator()(Binary& expr)
{
    return parenthesize(expr.oper.lexeme, { expr.left.get(), expr.right.get() });
}

Literal AstPrinter::operator()(Grouping& expr)
{
    return parenthesize("group", { expr.expression.get() });
}

Literal AstPrinter::operator()(Lit& expr)
{
    if (std::holds_alternative<double>(expr.value)) {
        return std::to_string(std::get<double>(expr.value));
    } else if (std::holds_alternative<std::string>(expr.value)) {
        return std::get<std::string>(expr.value);
    } else if(std::holds_alternative<bool>(expr.value)) {
        return std::get<bool>(expr.value) ? "true" : "false";
    }
    else {
        Cpplox::error(6969, "no such variant in expression");
        return "wrong ass variant";
    }
}

Literal AstPrinter::operator()(Unary& expr)
{
    return parenthesize(expr.oper.lexeme, { expr.right.get() });
}
