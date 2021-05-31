#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

enum class CHAR_TYPE { up_char, low_char, num_char, spec_char };
enum class ML_MODE { random = 1, forward, backward };

inline bool IsValidInt(int num, bool limit_shift = false);
inline bool IsValidMLMode(int num);

class PasswordGenerator {
private:
    int m_length = 8;
    bool m_random_length = false;
    int m_cur_mask_idx = 0;
    std::mt19937_64 m_rnd_gen;
    std::uniform_int_distribution<int> m_lim_chr_gen;
    std::uniform_int_distribution<int> m_lim_mask_mode;
    std::uniform_int_distribution<int> m_lim_use_syms;
    ML_MODE m_mlm = ML_MODE::forward;
    std::vector<std::string> m_masks;
    std::vector<CHAR_TYPE> m_usable_syms;
    std::vector<char> m_custom_chars;

public:
    char GenerateRandomChar(CHAR_TYPE char_type);
    char GenerateMaskChar(char symbol);
    void SetPasswordMask(const std::string& mask);
    void SetPasswordMasks(std::vector<std::string> mask);
    void SetPasswordLength(int len);
    void UseRandomPasswordLength(bool m_random_length);
    void SetPasswordSeed(int se);
    void SetPasswordMaskMode(ML_MODE mlm);
    void SetUsableSyms(const std::string& syms);
    void SetCustomAlphabet(std::vector<char>& alpha);

    std::string GeneratePassword();
    PasswordGenerator();
};
