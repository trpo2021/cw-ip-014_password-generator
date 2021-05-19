#pragma once
#include <iostream>
#include <random>

enum class CHAR_TYPE { UP_CHAR, LOW_CHAR, NUM_CHAR, SPEC_CHAR };

class PasswordGenerator {
private:
    std::mt19937_64 m_rnd_gen;
    int m_amount = 1;
    int m_length = 8;
    bool m_random_length = false;
    inline bool IsValidInt(int num, bool limit_shift = false);
    std::string m_mask;
    std::uniform_int_distribution<int> limit_for_random;

public:
    char GenerateRandomChar(CHAR_TYPE char_type);
    char GenerateMaskChar(char symbol);
    void SetPasswordMask(const std::string& mask);
    void SetPasswordLength(int len);
    void UseRandomPasswordLength(bool m_random_length);
    void SetPasswordSeed(int se);

    std::string GeneratePassword();
    PasswordGenerator() : m_rnd_gen(time(NULL))
    {
    }
};
