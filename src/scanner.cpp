#include "scanner.hpp"
#include "cpplox.hpp"
#include "token.hpp"

std::unordered_map<std::string, TokenType> Scanner::keywords = {
    { "and", AND },
    { "class", CLASS },
    { "else", ELSE },
    { "false", FALSE },
    { "for", FOR },
    { "fun", FUN },
    { "if", IF },
    { "nil", NIL },
    { "or", OR },
    { "print", PRINT },
    { "return", RETURN },
    { "super", SUPER },
    { "this", THIS },
    { "true", TRUE },
    { "var", VAR },
    { "while", WHILE },
};

std::vector<Token> Scanner::scan_tokens()
{
    while (not is_at_end()) {
        start = current;
        scan_token();
    }

    tokens.push_back(Token { TOKEN_EOF, "", Literal { "" }, line });
    return tokens;
}

void Scanner::scan_token()
{
    char c = advance();
    switch (c) {
    case '(':
        add_token(LEFT_PAREN);
        break;
    case ')':
        add_token(RIGHT_PAREN);
        break;
    case '{':
        add_token(LEFT_BRACE);
        break;
    case '}':
        add_token(RIGHT_BRACE);
        break;
    case ',':
        add_token(COMMA);
        break;
    case '.':
        add_token(DOT);
        break;
    case '-':
        add_token(MINUS);
        break;
    case '+':
        add_token(PLUS);
        break;
    case ';':
        add_token(SEMICOLON);
        break;
    case '*':
        add_token(STAR);
        break;
    case '!':
        add_token(match('=') ? BANG_EQUAL : BANG);
        break;
    case '=':
        add_token(match('=') ? EQUAL_EQUAL : EQUAL);
        break;
    case '<':
        add_token(match('=') ? LESS_EQUAL : LESS);
        break;
    case '>':
        add_token(match('=') ? GREATER_EQUAL : GREATER);
        break;
    case '/':
        if (match('/')) {
            // A comment goes until the end of the line.
            while (peek() != '\n' && !is_at_end())
                advance();
        } else {
            add_token(SLASH);
        }
        break;

    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    case '\n':
        line++;
        break;

    case '"':
        string();
        break;

    default:
        if (isdigit(c)) {
            number();
        } else if (isalpha(c)) {
            identifier();
        } else {
            Cpplox::error(line, "Unexpected character.");
        }
        break;
    }
}

void Scanner::identifier()
{
    while (isalnum(peek()))
        advance();

    std::string text = src.substr(start, current - start);
    TokenType type = keywords.find(text) != keywords.end() ? keywords[text] : IDENTIFIER;
    add_token(type);
}

void Scanner::string()
{
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n')
            line++;
        advance();
    }
    if (is_at_end()) {
        Cpplox::error(line, "Unterminated string.");
        return;
    }
    // The closing ".
    advance();
    // Trim the surrounding quotes.
    std::string value = src.substr(start + 1, current - start - 2);
    add_token(STRING, value);
}

void Scanner::number()
{
    while (isdigit(peek()))
        advance();
    // Look for a fractional part.
    if (peek() == '.' && isdigit(peek_next())) {
        // Consume the "."
        advance();
        while (isdigit(peek()))
            advance();
    }
    add_token(NUMBER, Literal { std::stod(src.substr(start, current - start)) });
}

char Scanner::peek_next()
{
    if (current + 1 >= src.size())
        return '\0';
    return src[current + 1];
}

bool Scanner::match(char expected)
{
    if (is_at_end())
        return false;
    if (src[current] != expected)
        return false;
    current++;
    return true;
}

char Scanner::advance()
{
    current++;
    return src[current - 1];
}

void Scanner::add_token(TokenType type)
{
    add_token(type, Literal { "" });
}

char Scanner::peek()
{
    if (is_at_end())
        return '\0';
    return src[current];
}

void Scanner::add_token(TokenType type, Literal lit)
{
    std::string text = src.substr(start, current - start);
    tokens.push_back(Token { type, text, lit, line });
}

bool Scanner::is_at_end()
{
    return current >= src.length();
}
