#include "PasswordGenerator.h"
#include "argh.h"
#include <iostream>

int main(int argc, char* argv[])
{
    PasswordGenerator pgen;
    auto cmdl = argh::parser(argc, argv);
    cmdl.parse(argc, argv, argh::parser::Mode::PREFER_PARAM_FOR_UNREG_OPTION);
    for (int a = 0; a < std::stoi(cmdl({"--count","-c"}, 1).str()); a++) {
        std::cout << pgen.GeneratePassword() << "\n";
    }
}
