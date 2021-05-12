#include "PasswordGenerator.h"

const std::string CHARS_ARRAY
        = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%"
          "&'()*+,-./:;<=>?@";
const std::uniform_int_distribution<int> NUM_LET_LIMIT(0, 9);
const std::uniform_int_distribution<int> LOW_LET_LIMIT(10, 35);
const std::uniform_int_distribution<int> UP_LET_LIMIT(36, 62);
const std::uniform_int_distribution<int> SPEC_SYM_LIMIT(63, 84);

inline bool PasswordGenerator::IsValidInt(int num)
{
    return (num > 1 && num < INT_MAX - 1);
}

char PasswordGenerator::GenerateRandomChar(CHAR_TYPE char_type)
{
    switch (char_type) {
    case CHAR_TYPE::UP_LETTER:
        return CHARS_ARRAY[UP_LET_LIMIT(rnd_gen)];
        break;
    case CHAR_TYPE::LOW_LETTER:
        return CHARS_ARRAY[LOW_LET_LIMIT(rnd_gen)];
        break;
    case CHAR_TYPE::NUM_LETTER:
        return CHARS_ARRAY[NUM_LET_LIMIT(rnd_gen)];
        break;
    case CHAR_TYPE::SPEC_SYMBOL:
        return CHARS_ARRAY[SPEC_SYM_LIMIT(rnd_gen)];
        break;
    default:
        return '0'; // must be impossible because it only accepts CHAR_TYPE....
        break;
    }
}

std::string PasswordGenerator::GeneratePassword()
{
    std::string pass;
    pass.resize(length + 1);
    for (auto& x : pass)
        x = GenerateRandomChar(CHAR_TYPE::LOW_LETTER);
    return pass;
}

void PasswordGenerator::SetPasswordsLength(int len)
{
    if (IsValidInt(len))
        len = len;
    else
        std::cout << "Set amount of generated passwords is incorrect.\n";
}
