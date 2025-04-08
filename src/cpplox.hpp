#pragma once
#include "common.hpp"
#include "interpretor.hpp"
#include "token.hpp"

class Cpplox {
private:
    static Interpretor interpretor;
    static void run(std::string src);
    static bool had_error;
    static bool had_runtime_error;
    static void error(Token token, std::string msg);
    static void report(int line, std::string where, std::string msg);

public:
    static void error(int line, std::string msg);
    static void runtime_error(Interpretor::RuntimeError error);
    static void run_file(std::string file);
    static void run_prompt();

    friend class Scanner;
    friend class Parser;
};
