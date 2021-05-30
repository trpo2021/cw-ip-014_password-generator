#include "PasswordGenerator.h"
#include <climits>

const std::string CHARS_ARRAY
        = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%"
          "&'()*+,-./:;<=>?@";
std::uniform_int_distribution<int> NUM_LET_LIMIT(0, 9);
std::uniform_int_distribution<int> LOW_LET_LIMIT(10, 35);
std::uniform_int_distribution<int> UP_LET_LIMIT(36, 61);
std::uniform_int_distribution<int> SPEC_SYM_LIMIT(63, 84);

inline bool IsValidInt(int num, bool limit_shift)
{
    return (num >= (limit_shift == true ? 1 : 0) && num <= INT_MAX - 1);
}

char PasswordGenerator::GenerateRandomChar(CHAR_TYPE char_type)
{
    switch (char_type) {
    case CHAR_TYPE::up_char:
        return CHARS_ARRAY[UP_LET_LIMIT(m_rnd_gen)];
    case CHAR_TYPE::low_char:
        return CHARS_ARRAY[LOW_LET_LIMIT(m_rnd_gen)];
    case CHAR_TYPE::num_char:
        return CHARS_ARRAY[NUM_LET_LIMIT(m_rnd_gen)];
    case CHAR_TYPE::spec_char:
        return CHARS_ARRAY[SPEC_SYM_LIMIT(m_rnd_gen)];
    default:
        return '0'; // must be impossible because it only accepts CHAR_TYPE....
    }
}

char PasswordGenerator::GenerateMaskChar(char symbol)
{
    switch (symbol) {
    case 'L':
        return GenerateRandomChar(CHAR_TYPE::low_char);
    case 'U':
        return GenerateRandomChar(CHAR_TYPE::up_char);
    case 'N':
        return GenerateRandomChar(CHAR_TYPE::num_char);
    case 'S':
        return GenerateRandomChar(CHAR_TYPE::spec_char);
    default:
        return symbol;
    }
}

std::string PasswordGenerator::GeneratePassword()
{
    std::string pass;

    if (m_mask.empty()) {
        pass.resize(m_length + 1);
        if (m_random_length == true) {
            limit_for_random = std::uniform_int_distribution<int>(1, m_length);
            pass.resize(limit_for_random(m_rnd_gen));
        }
        for (auto& x : pass)
            x = GenerateRandomChar(CHAR_TYPE::low_char);
        return pass;
    } else {
        if (m_cur_mask_idx >= m_mask.size())
            m_cur_mask_idx = 0;

        pass.resize(m_mask[m_cur_mask_idx].length() + 1);
        for (int a = 0; a < pass.size(); a++)
            pass[a] = GenerateMaskChar(m_mask[m_cur_mask_idx][a]);

        m_cur_mask_idx++;
        return pass;
    }
}

void PasswordGenerator::SetPasswordMask(const std::string& mask)
{
    m_mask.clear();
    m_mask.push_back(mask);
}

void PasswordGenerator::SetPasswordLength(int len)
{
    if (IsValidInt(len, true)) {
        m_length = len - 1;
    } else
        std::cout << "Set amount of generated passwords is incorrect.\n";
}

void PasswordGenerator::SetPasswordSeed(int se)
{
    if (IsValidInt(se))
        m_rnd_gen.seed(se);
    else
        std::cout << "Set seed is incorrrect.\n";
}

void PasswordGenerator::UseRandomPasswordLength(bool random_length)
{
    m_random_length = random_length;
}

void PasswordGenerator::SetPasswordMasks(std::vector<std::string> mask)
{
    m_mask = mask;
}