#include "PasswordGenerator.h"
#include "argh.h"
#include <fstream>
#include <iostream>

class PassGenFrontend {
private:
    bool is_console = true;
    argh::parser cmdl = argh::parser();
    PasswordGenerator pgen;

public:
    void ActivateCustomAlphabet();
    void ActivateMLMode();
    void OutputPasswords();
    int GetCmdInt(std::initializer_list<char const* const> init_list, int def_val);
    PassGenFrontend(int argc, char* argv[]);
};
