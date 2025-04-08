#include "cpplox.hpp"

int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "Usage : cpplox [script]\n";
        exit(69);
    } else if (argc == 2) {
        Cpplox::run_file(argv[1]);
    } else {
        Cpplox::run_prompt();
    }
}
