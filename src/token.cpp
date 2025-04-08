#include "token.hpp"

std::ostream& operator<<(std::ostream& out, const Token& t)
{
    if (std::holds_alternative<double>(t.literal)) {
        out << t.type << " " << t.lexeme << " " << std::get<double>(t.literal);
    } else if (std::holds_alternative<std::string>(t.literal)) {
        out << t.type << " " << t.lexeme << " " << std::get<std::string>(t.literal);
    } else if (std::holds_alternative<bool>(t.literal)) {
    out << t.type << " " << t.lexeme << (std::get<bool>(t.literal) ? " true" : " false");
    } else {
        out << t.type << " " << t.lexeme << " " << "invalid type";
    }

    return out;
}
