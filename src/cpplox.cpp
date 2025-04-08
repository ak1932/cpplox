#include "cpplox.hpp"
#include "astprinter.hpp"
#include "parser.hpp"
#include "scanner.hpp"

bool Cpplox::had_error = false;
bool Cpplox::had_runtime_error = false;
Interpretor Cpplox::interpretor;

void Cpplox::run_file(std::string file)
{
    std::fstream fs(file);
    if (!fs.is_open()) {
        std::cerr << "file no open\n";
        std::exit(1);
    }

    std::string str(std::istreambuf_iterator<char> { fs }, {});

    run(str);
    if (had_error) std::exit(65);
    if (had_runtime_error) std::exit(70);
}

void Cpplox::run_prompt()
{
    while (true) {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        if (line == "")
            break;
        run(line);
        had_error = false;
        had_runtime_error = false;
    }
}

void Cpplox::runtime_error(Interpretor::RuntimeError r_err)
{
    std::cerr << r_err.what() << "\n[line: " << r_err.token.line << "]";
    had_runtime_error = true;
}

void Cpplox::error(int line, std::string msg)
{
    report(line, "", msg);
}

void Cpplox::report(int line, std::string where, std::string msg)
{
    std::cout << "[line " << line << "] Error" << where << ": " << msg << "\n";
    had_error = true;
}

void Cpplox::error(Token token, std::string msg)
{
    if (token.type == TOKEN_EOF) {
        report(token.line, " at end", msg);
    } else {
        report(token.line, " at " + token.lexeme + "'", msg);
    }
}

void Cpplox::run(std::string src)
{
    Scanner sc(src);
    std::vector<Token> tokens = sc.scan_tokens();
    Parser parser(tokens);

    std::vector<Stmt> statements = parser.parse();
    if(had_error) return;

    interpretor.interpret(statements);
}
