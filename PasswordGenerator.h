#pragma once
#include <iostream>
#include <random>
#include <vector>

enum class CHAR_TYPE { up_char, low_char, num_char, spec_char };
enum class ML_MODE { random=1, forward, backward };

inline bool IsValidInt(int num, bool limit_shift = false);
inline bool IsValidMLMode(int num);

class PasswordGenerator {
private:
    std::mt19937_64 m_rnd_gen;
    int m_length = 8;
    bool m_random_length = false;
    std::vector<std::string> m_mask;
    int m_cur_mask_idx = 0;
    std::uniform_int_distribution<int> m_limit_for_random;
    std::uniform_int_distribution<int> m_lim_mask_mode;
    ML_MODE m_mlm = ML_MODE::forward;

public:
    char GenerateRandomChar(CHAR_TYPE char_type);
    char GenerateMaskChar(char symbol);
    void SetPasswordMask(const std::string& mask);
    void SetPasswordMasks(std::vector<std::string> mask);
    void SetPasswordLength(int len);
    void UseRandomPasswordLength(bool m_random_length);
    void SetPasswordSeed(int se);
    void SetPasswordMaskMode(ML_MODE mlm);

    std::string GeneratePassword();
    PasswordGenerator() : m_rnd_gen(time(NULL))
    {
    }
};
