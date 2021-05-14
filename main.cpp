#include "PasswordGenerator.h"
#include "argh.h"
#include <fstream>
#include <iostream>

auto cmdl = argh::parser();

int GetCmdInt(std::initializer_list<char const* const> init_list, int def_val)
{
    std::string tmp = cmdl(init_list, def_val).str();
    try {
        return std::stoi(tmp);
    } catch (std::exception& ex) {
        std::cout << tmp << " is not a valid integer value\n";
        return def_val;
    }
}

int main(int argc, char* argv[])
{
    std::ofstream ot;
    PasswordGenerator pgen;
    cmdl.parse(argc, argv, argh::parser::Mode::PREFER_PARAM_FOR_UNREG_OPTION);
    pgen.SetPasswordLength(GetCmdInt({"--length", "-l"}, 1));
    pgen.SetPasswordMask(cmdl({"--mask", "-m"}, "").str());
    pgen.SetPasswordSeed(GetCmdInt({"--seed", "-se"}, time(NULL)));
    std::string seperator = cmdl({"--seperator", "-s"}, '\n').str();
    std::string out_file = cmdl({"--outFile", "-of"}, "").str();
    if (out_file.empty()) {
        for (int a = 0; a < GetCmdInt({"--count", "-c"}, 1); a++) {
            std::cout << pgen.GeneratePassword() << seperator;
        }
    } else {
        ot.open(out_file);
        for (int a = 0; a < GetCmdInt({"--count", "-c"}, 1); a++) {
            ot << pgen.GeneratePassword() << seperator;
        }
    }
}
