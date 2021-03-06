#include "PassGenFrontend.h"
#include "PasswordGenerator.h"
#include "argh.h"
#include <fstream>
#include <iostream>

int PassGenFrontend::GetCmdInt(
        std::initializer_list<char const* const> init_list, int def_val)
{
    std::string tmp = cmdl(init_list, def_val).str();
    try {
        return std::stoi(tmp);
    } catch (std::exception& ex) {
        std::cout << tmp << " is not a valid integer value\n";
        return def_val;
    }
}

PassGenFrontend::PassGenFrontend(int argc, char* argv[])
{
    cmdl.parse(argc, argv, argh::parser::Mode::PREFER_PARAM_FOR_UNREG_OPTION);

    if (pgen.SetPasswordLength(GetCmdInt({"--length", "-l"}, 8)) == false)
        std::cout << "Set password length is incorrect.\n";

    if (pgen.SetPasswordSeed(GetCmdInt({"--seed", "-se"}, time(NULL))) == false)
        std::cout << "Set seed is incorrrect.\n";

    if (pgen.SetPasswordMaskMode(
                ML_MODE(GetCmdInt({"--mlMode", "-mlm"}, int(ML_MODE::forward))))
        == false)
        std::cout << "Invalid mask list mode.\n";

    pgen.UseRandomPasswordLength(cmdl[{"--passRndLen", "-rl"}]);
    pgen.SetUsableSyms(cmdl({"--useSyms", "-us"}, "L").str());

    ActivateCustomAlphabet();
    ActivateMLMode();
    OutputPasswords();
}

void PassGenFrontend::ActivateCustomAlphabet()
{
    std::string alphabet_file = cmdl({"--customAlphabetList", "-al"}, "").str();
    if (alphabet_file.empty())
        return;

    std::ifstream in_stream(alphabet_file);

    if (!in_stream.is_open()) {
        std::cout << "Custom alphabet file " << alphabet_file << " not found\n";
    } else {
        std::vector<char> symbols;
        std::string buf;
        while (std::getline(in_stream, buf, ' ')) {
            if (buf.size() > 0)
                symbols.push_back(buf[0]);
        }
        if (symbols.size() != 0)
            pgen.SetCustomAlphabet(symbols);
        else
            std::cout << "Warning! Custom alphabet list is empty. Fallback to "
                         "defaults.\n";
    }
}

void PassGenFrontend::ActivateMLMode()
{
    std::string mask_file = cmdl({"--maskList", "-ml"}, "").str();
    if (mask_file.empty()) {
        pgen.SetPasswordMask(cmdl({"--mask", "-m"}, "").str());
        return;
    }
    std::ifstream in_stream(mask_file);

    if (in_stream.is_open()) {
        std::vector<std::string> masks;
        std::string buf;
        while (std::getline(in_stream, buf))
            masks.push_back(buf);

        if (masks.size() != 0)
            pgen.SetPasswordMasks(masks);
        else
            std::cout << "Warning! Custom alphabet list is empty. Fallback to "
                         "defaults.\n";
    } else
        std::cout << "Masklist " << mask_file << " not found\n";
}

void PassGenFrontend::OutputPasswords()
{
    std::string seperator = cmdl({"--seperator", "-s"}, '\n').str();
    std::string out_file = cmdl({"--outFile", "-of"}, "").str();
    std::ofstream out_stream;
    if (!out_file.empty()) {
        out_stream.open(out_file);
        if (out_stream.is_open())
            is_console = false;
    }

    for (int a = 0; a < GetCmdInt({"--count", "-c"}, 8); a++) {
        if (is_console)
            std::cout << pgen.GeneratePassword() << seperator;
        else
            out_stream << pgen.GeneratePassword() << seperator;
    }
}
