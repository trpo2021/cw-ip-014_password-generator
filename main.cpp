#include "PasswordGenerator.h"
#include "argh.h"
#include <fstream>
#include <iostream>

auto cmdl = argh::parser();
void Help()
{
    std::cout << "If you want to set count of passwords use function "
                 "--count(-c)\n"
                 "Standart count of passwords is 1\n\n";
    std::cout << "If you want to set length of passwords use function "
                 "--len (-l)\n"
                 "Standart length of passwords is 8 symbols\n\n";
    std::cout << "If you want to set string separating the passwords use "
                 "function --separator (-sp)\n"
                 "Standart separation is (\\n)\n\n";
    std::cout << "If you want to use mask use function --mask (-m)\n"
                 "If you use mask parameters responsible for the type of "
                 "characters used and the length are ignored.\n"
                 "You can use the following parameters for the mask : \n"
                 "N - there must be a numeric symbol in place of the "
                 "symbol\n"
                 "L - lower case letter in place of the symbol\n"
                 "U - upper case letter in place of the symbol\n"
                 "S - symbol must be replaced by a special character\n"
                 "To see a list of masks, use the command --maskList (-ml)\n"
                 "When this parameter is used, the -mask parameter is "
                 "ignored.\n\n";
    std::cout << "--mlMode (-mlm) Sets how a mask is selected from the "
                 "mask list (-maskList).\n"
                 "The value must be an integer, which is one of the "
                 "possible parameters.\n"
                 "Possible parameters:\n"
                 "1 - Select the masks in random order.\n2- Select masks "
                 "sequentially from the beginning of the file.\n3- Select "
                 "masks sequentially from the end of the file.\nDefault "
                 "value: 2\n\n";
    std::cout << "--useSyms (-us) Sets the characters allowed to be used "
                 "when generating a password\nN - password can contain "
                 "numeric characters\nL - password can contain lower case "
                 "letters.\nU - password can contain uppercase letters.\nS "
                 "- password can contain special symbols.\nStandard "
                 "value: \"SL\"\n\n";
    std::cout << "--outFile (-of) Path to file where passwords will be "
                 "written to.\n"
                 "If the file doesn't exist, the program creates it, if it "
                 "does, it adds the generated passwords to the end of the "
                 "file.\n\n"
                 "Parameter value must be correct path\n";
    std::cout << "--seed (-se) Sets the seed for the random number "
                 "generator.\n"
                 "Allows for identical sets of random characters.\n"
                 "The value must be a valid integer.\n\n";
    std::cout << "--passRndLen (-rl)\n Activates setting a random password "
                 "length from 1 to the value of -len parameter after each "
                 "password generation.\n";
    std::cout << "--customAlphabetList (-al) Path to list of characters "
                 "used in password generation.\nThe parameter value must "
                 "be the correct path to the list file.\n The list is a "
                 "text file containing characters separated by a space "
                 "character ' '\n.\n";
}

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
    if (argc != 1) {
        std::ofstream ot;
        std::ifstream masks_stream;
        PasswordGenerator pgen;
        cmdl.parse(
                argc, argv, argh::parser::Mode::PREFER_PARAM_FOR_UNREG_OPTION);
        pgen.SetPasswordLength(GetCmdInt({"--length", "-l"}, 8));
        pgen.UseRandomPasswordLength(cmdl[{"--passRndLen", "-rl"}]);
        pgen.SetPasswordSeed(GetCmdInt({"--seed", "-se"}, time(NULL)));
        pgen.SetPasswordMaskMode(ML_MODE(GetCmdInt({"--mlMode", "-mlm"},int(ML_MODE::forward))));
        std::cout << GetCmdInt({"--mlMode", "-mlm"},int(ML_MODE::forward)) << "\n";
        std::string seperator = cmdl({"--seperator", "-s"}, '\n').str();
        std::string out_file = cmdl({"--outFile", "-of"}, "").str();
        std::string mask_file = cmdl({"--maskList", "-ml"}, "").str();

        const bool is_mask_file = !mask_file.empty();
        if (is_mask_file) {
            masks_stream.open(mask_file);
            if (masks_stream.is_open()) {
                std::vector<std::string> masks;
                std::string buf;
                while (std::getline(masks_stream, buf))

                    masks.push_back(buf);
                pgen.SetPasswordMasks(masks);
            } else
                std::cout << "Masklist " << mask_file << " not found";
        } else
            pgen.SetPasswordMask(cmdl({"--mask", "-m"}, "").str());

        const bool is_console = out_file.empty();
        if (!is_console) {
            ot.open(out_file);
            if (masks_stream.is_open())
                std::cout << "Outfile " << mask_file << " not found";
        }

        for (int a = 0; a < GetCmdInt({"--count", "-c"}, 8); a++) {
            if (is_console)
                std::cout << pgen.GeneratePassword() << seperator;
            else
                ot << pgen.GeneratePassword() << seperator;
        }

    } else {
        Help();
    }
}
