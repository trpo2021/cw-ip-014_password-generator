#include "PasswordGenerator.h"
#include <climits>

const std::string CHARS_ARRAY
        = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%"
          "&'()*+,-./:;<=>?@";
std::uniform_int_distribution<int> NUM_LET_LIMIT(0, 9);
std::uniform_int_distribution<int> LOW_LET_LIMIT(10, 35);
std::uniform_int_distribution<int> UP_LET_LIMIT(36, 61);
std::uniform_int_distribution<int> SPEC_SYM_LIMIT(63, 84);

PasswordGenerator::PasswordGenerator() : m_rnd_gen(time(NULL))
{
    m_usable_syms.push_back(CHAR_TYPE::low_char);
    m_lim_use_syms = std::uniform_int_distribution<int>(0, 0);
}

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
    if (m_masks.size() != 0 && m_masks[0] == "")
        m_masks.clear();

    if (m_masks.empty()) {
        pass.resize(m_length + 1);
        if (m_random_length == true) {
            m_lim_chr_gen = std::uniform_int_distribution<int>(1, m_length);
            pass.resize(m_lim_chr_gen(m_rnd_gen));
        }
        for (auto& x : pass) {
            if (m_custom_chars.size() == 0)
                x = GenerateRandomChar(
                        m_usable_syms[m_lim_use_syms(m_rnd_gen)]);
            else
                x = m_custom_chars[m_lim_use_syms(m_rnd_gen)];
        }
        return pass;
    } else {
        // set inital idx if using multiple masks mode
        if (m_mlm == ML_MODE::forward && m_cur_mask_idx == m_masks.size())
            m_cur_mask_idx = 0;
        else if (m_mlm == ML_MODE::backward && m_cur_mask_idx == -1)
            m_cur_mask_idx = m_masks.size() - 1;
        else if (m_mlm == ML_MODE::random)
            m_cur_mask_idx = m_lim_mask_mode(m_rnd_gen);

        pass.resize(m_masks[m_cur_mask_idx].length() + 1);
        for (int a = 0; a < pass.size(); a++)
            pass[a] = GenerateMaskChar(m_masks[m_cur_mask_idx][a]);

        if (m_mlm == ML_MODE::forward)
            m_cur_mask_idx++;
        else if (m_mlm == ML_MODE::backward)
            m_cur_mask_idx--;
        else
            m_cur_mask_idx = m_lim_mask_mode(m_rnd_gen);

        return pass;
    }
}

void PasswordGenerator::SetPasswordMask(const std::string& mask)
{
    m_masks.clear();
    m_masks.push_back(mask);
}

void PasswordGenerator::SetPasswordLength(int len)
{
    if (IsValidInt(len, true))
        m_length = len - 1;
    else
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
    if (mask.empty())
        return;
    m_masks = mask;
    m_lim_mask_mode = std::uniform_int_distribution<int>(0, mask.size() - 1);
}

void PasswordGenerator::SetPasswordMaskMode(ML_MODE mlm)
{
    if (IsValidMLMode(int(mlm))) {
        m_mlm = mlm;
        if (m_mlm == ML_MODE::backward)
            m_cur_mask_idx = m_masks.size() - 1;
    } else
        std::cout << "Invalid mask list mode.\n";
}

inline bool IsValidMLMode(int num)
{
    if (num >= int(ML_MODE::random) && num <= int(ML_MODE::backward))
        return true;
    else
        return false;
}

void PasswordGenerator::SetUsableSyms(const std::string& syms)
{
    m_usable_syms.clear();

    for (auto& x : syms) {
        if (x == 'L')
            m_usable_syms.push_back(CHAR_TYPE::low_char);
        else if (x == 'U')
            m_usable_syms.push_back(CHAR_TYPE::up_char);
        else if (x == 'N')
            m_usable_syms.push_back(CHAR_TYPE::num_char);
        else if (x == 'S')
            m_usable_syms.push_back(CHAR_TYPE::spec_char);
    }

    m_usable_syms.erase(
            std::unique(m_usable_syms.begin(), m_usable_syms.end()),
            m_usable_syms.end());

    m_lim_use_syms
            = std::uniform_int_distribution<int>(0, m_usable_syms.size() - 1);
}

void PasswordGenerator::SetCustomAlphabet(std::vector<char>& alpha)
{
    m_custom_chars = alpha;
    m_lim_use_syms
            = std::uniform_int_distribution<int>(0, m_custom_chars.size() - 1);
}