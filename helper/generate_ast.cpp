#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>

void generate_file_for_ast(std::string basename, std::vector<std::string> def_ast, std::string filename, std::vector<std::string> headers, std::vector<std::string> basenames);

int main(int argc, char** argv)
{
    std::vector<std::string> expr_ast = {
        "Binary: Expr left, Token oper, Expr right",
        "Grouping: Expr expression",
        "Lit: Literal value",
        "Unary: Token oper, Expr right",
        "Variable: Token name"
    };

    std::vector<std::string> stmt_ast = {
        "Expression: Expr expression",
        "Print: Expr expression",
        "Var: Token name, Expr initializer"
    };

    generate_file_for_ast("Expr", expr_ast, "expr.hpp", { "#include \"token.hpp\"" }, { "Expr", "Stmt" });
    generate_file_for_ast("Stmt", stmt_ast, "stmt.hpp", { "#include \"expr.hpp\"" }, { "Expr", "Stmt" });
}

void generate_file_for_ast(std::string basename, std::vector<std::string> def_ast, std::string filename, std::vector<std::string> headers, std::vector<std::string> basenames)
{
    std::string preprocessor_directives = "#pragma once\n\n";

    std::string base_class = "";
    std::string ind_class = "";

    std::string auto_gen_warning = "/* Auto generated using helper method generate_ast() for the CFG\n";

    for (auto def : def_ast) {
        auto_gen_warning += def + "\n";
    }
    auto_gen_warning += "*/\n";

    std::string class_def = "";

    base_class += "using " + basename + " = std::variant<"; // + Binary, Grouping, Lit, Unary>;
    for (auto c : def_ast) {
        std::string class_name = c.substr(0, c.find(": "));
        class_def += "class " + class_name + ";\n";
        base_class += class_name + ", ";
    }
    class_def += "\n";
    base_class = base_class.substr(0, base_class.size() - 2);
    base_class += ">;\n\n";

    for (auto c : def_ast) {
        std::string class_name = c.substr(0, c.find(": "));
        int param_start = c.find(": ") + 2;
        std::string params = c.substr(param_start);
        std::string members = "";

        ind_class += "class " + class_name + "{\n";
        ind_class += "public:\n";

        int index = 0;
        int sindex;

        std::string constructor_params = "";
        std::string constructor_signature = class_name + "(";

        while ((sindex = params.find(", ", index)) != params.npos) {
            std::string param = params.substr(index, sindex - index);

            std::string type = param.substr(0, param.find(" "));
            std::string val = param.substr(param.find(" ") + 1);

            if (std::find(basenames.begin(), basenames.end(), type) != basenames.end()) {
                constructor_signature += "std::unique_ptr<" + type + ">&& " + val + ", ";
                constructor_params += val + "(std::move(" + val + ")), ";
                members += "std::unique_ptr<" + type + "> " + val + ";\n";
            } else {
                constructor_signature += param + ", ";
                constructor_params += val + "(" + val + "), ";
                members += param + ";\n";
            }
            index = sindex + 2;
        }

        std::string param = params.substr(index);
        std::string type = param.substr(0, param.find(" "));
        std::string val = param.substr(param.find(" ") + 1);

        if (std::find(basenames.begin(), basenames.end(), type) != basenames.end()) {
            constructor_signature += "std::unique_ptr<" + type + ">&& " + val + ")";
            constructor_params += val + "(std::move(" + val + ")) ";
            members += "std::unique_ptr<" + type + "> " + val + ";\n";
        } else {
            constructor_signature += param + ")";
            constructor_params += val + "(" + val + ") ";
            members += param + ";\n";
        }

        constructor_params += " {}\n\n";

        std::string constructor = constructor_signature + " : " + constructor_params;

        ind_class += constructor;

        // ind_class += "Literal accept(Visitor& visitor) override {\n";
        // ind_class += "return visitor.visit" + class_name + basename + "(*this);\n";
        // ind_class += "}\n\n";
        //
        ind_class += members;
        ind_class += "};\n\n";
    }

    std::string header_lines = "";
    for (auto header : headers) {
        header_lines += header + "\n";
    }
    header_lines += "\n";

    std::string final_file = preprocessor_directives + auto_gen_warning + header_lines + class_def + base_class + ind_class;

    std::cout << final_file;

    std::fstream fs(filename, std::fstream::out);

    if (not fs.is_open()) {
        std::cerr << "error opening file " << filename << "\n";
        std::exit(1);
    }
    fs << final_file;

    fs.close();
}
