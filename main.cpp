#include "PasswordGenerator.h"
#include "argh.h"
#include <iostream>

auto cmdl = argh::parser();

int GetCmdInt(std::initializer_list<char const* const> init_list, int def_val)
{
    return std::stoi(cmdl(init_list, def_val).str());
}

int main(int argc, char* argv[])
{
    PasswordGenerator pgen;
    cmdl.parse(argc, argv, argh::parser::Mode::PREFER_PARAM_FOR_UNREG_OPTION);
    pgen.SetPasswordsLength(GetCmdInt({"--length", "-l"}, 1));

    std::string seperator = cmdl({"--seperator", "-s"}, '\n').str();

    for (int a = 0; a < GetCmdInt({"--count", "-c"}, 1); a++) {
        std::cout << pgen.GeneratePassword() << seperator;
    }
}
