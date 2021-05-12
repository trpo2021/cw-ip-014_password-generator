#include "PasswordGenerator.h"
#include "argh.h"
#include <iostream>

void InitCmdArgs(argh::parser& parser, int argc, char* argv[])
{
    parser.add_params({"--count", "-c"});
    parser.parse(argc, argv);
}

int main(int argc, char* argv[])
{
    PasswordGenerator pgen;
    auto cmdl = argh::parser(argc, argv);
    InitCmdArgs(cmdl, argc, argv);
    for (int a = 0; a < stoi(cmdl("--count", 1).str()); a++) {
        std::cout << pgen.GeneratePassword();
    }
}
