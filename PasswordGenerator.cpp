#include "PasswordGenerator.h"
#include <climits>

const std::string CHARS_ARRAY
        = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%"
          "&'()*+,-./:;<=>?@";
std::uniform_int_distribution<int> NUM_LET_LIMIT(0, 9);
std::uniform_int_distribution<int> LOW_LET_LIMIT(10, 35);
std::uniform_int_distribution<int> UP_LET_LIMIT(36, 62);
std::uniform_int_distribution<int> SPEC_SYM_LIMIT(63, 84);

inline bool PasswordGenerator::IsValidInt(int num)
{
    return (num >= 1 && num <= INT_MAX - 1);
}

char PasswordGenerator::GenerateRandomChar(CHAR_TYPE char_type)
{
    switch (char_type) {
    case CHAR_TYPE::UP_CHAR:
        return CHARS_ARRAY[UP_LET_LIMIT(rnd_gen)];
        break;
    case CHAR_TYPE::LOW_CHAR:
        return CHARS_ARRAY[LOW_LET_LIMIT(rnd_gen)];
        break;
    case CHAR_TYPE::NUM_CHAR:
        return CHARS_ARRAY[NUM_LET_LIMIT(rnd_gen)];
        break;
    case CHAR_TYPE::SPEC_CHAR:
        return CHARS_ARRAY[SPEC_SYM_LIMIT(rnd_gen)];
        break;
    default:
        return '0'; // must be impossible because it only accepts CHAR_TYPE....
        break;
    }
}

char PasswordGenerator::GenerateMaskChar(char symbol)
{
    switch (symbol) {
    case 'L':
        return GenerateRandomChar(CHAR_TYPE::LOW_CHAR);
        break;
    case 'U':
        return GenerateRandomChar(CHAR_TYPE::UP_CHAR);
        break;
    case 'N':
        return GenerateRandomChar(CHAR_TYPE::NUM_CHAR);
        break;
    case 'S':
        return GenerateRandomChar(CHAR_TYPE::SPEC_CHAR);
        break;
    default:
        return symbol;
        break;
    }
}

std::string PasswordGenerator::GeneratePassword()
{
    std::string pass;
    if (mask.empty()) {
        pass.resize(length + 1);
        for (auto& x : pass)
            x = GenerateRandomChar(CHAR_TYPE::LOW_CHAR);
        return pass;
    } else {
        pass.resize(mask.length() + 1);
        for (int a = 0; a < pass.size(); a++)
            pass[a] = GenerateMaskChar(mask[a]);
        return pass;
    }
}

void PasswordGenerator::SetPasswordMask(std::string& mask)
{
    mask = mask;
}

void PasswordGenerator::SetPasswordLength(int len)
{
    if (IsValidInt(len))
        length = len;
    else
        std::cout << "Set amount of generated passwords is incorrect.\n";
}
