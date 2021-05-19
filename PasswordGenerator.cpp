#include "PasswordGenerator.h"
#include <climits>

const std::string CHARS_ARRAY
        = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%"
          "&'()*+,-./:;<=>?@";
std::uniform_int_distribution<int> NUM_LET_LIMIT(0, 9);
std::uniform_int_distribution<int> LOW_LET_LIMIT(10, 35);
std::uniform_int_distribution<int> UP_LET_LIMIT(36, 61);
std::uniform_int_distribution<int> SPEC_SYM_LIMIT(63, 84);

inline bool PasswordGenerator::IsValidInt(int num, bool limit_shift)
{
    return (num >= (limit_shift == true ? 1 : 0) && num <= INT_MAX - 1);
}

char PasswordGenerator::GenerateRandomChar(CHAR_TYPE char_type)
{
    switch (char_type) {
    case CHAR_TYPE::UP_CHAR:
        return CHARS_ARRAY[UP_LET_LIMIT(rnd_gen)];
    case CHAR_TYPE::LOW_CHAR:
        return CHARS_ARRAY[LOW_LET_LIMIT(rnd_gen)];
    case CHAR_TYPE::NUM_CHAR:
        return CHARS_ARRAY[NUM_LET_LIMIT(rnd_gen)];
    case CHAR_TYPE::SPEC_CHAR:
        return CHARS_ARRAY[SPEC_SYM_LIMIT(rnd_gen)];
    default:
        return '0'; // must be impossible because it only accepts CHAR_TYPE....
    }
}

char PasswordGenerator::GenerateMaskChar(char symbol)
{
    switch (symbol) {
    case 'L':
        return GenerateRandomChar(CHAR_TYPE::LOW_CHAR);
    case 'U':
        return GenerateRandomChar(CHAR_TYPE::UP_CHAR);
    case 'N':
        return GenerateRandomChar(CHAR_TYPE::NUM_CHAR);
    case 'S':
        return GenerateRandomChar(CHAR_TYPE::SPEC_CHAR);
    default:
        return symbol;
    }
}

std::string PasswordGenerator::GeneratePassword()
{
    std::string pass;
    if (m_mask.empty()) {
        pass.resize(length + 1);
        if (m_random_length == true) {
            limit_for_random = std::uniform_int_distribution<int>(1, length);
            pass.resize(limit_for_random(rnd_gen));
        }
        for (auto& x : pass)
            x = GenerateRandomChar(CHAR_TYPE::LOW_CHAR);
        return pass;
    } else {
        pass.resize(m_mask.length() + 1);
        for (int a = 0; a < pass.size(); a++)
            pass[a] = GenerateMaskChar(m_mask[a]);
        return pass;
    }
}

void PasswordGenerator::SetPasswordMask(const std::string& mask)
{
    m_mask = mask;
}

void PasswordGenerator::SetPasswordLength(int len)
{
    if (IsValidInt(len, true)) {
        length = len - 1;
    } else
        std::cout << "Set amount of generated passwords is incorrect.\n";
}

void PasswordGenerator::SetPasswordSeed(int se)
{
    if (IsValidInt(se))
        rnd_gen.seed(se);
    else
        std::cout << "Set seed is incorrrect.\n";
}

void PasswordGenerator::UseRandomPasswordLength(bool random_length)
{
    m_random_length = random_length;
}
