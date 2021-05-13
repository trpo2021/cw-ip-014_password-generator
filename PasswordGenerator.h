#pragma once
#include <iostream>
#include <random>

enum class CHAR_TYPE { UP_CHAR, LOW_CHAR, NUM_CHAR, SPEC_CHAR };

class PasswordGenerator {
private:
    std::mt19937_64 rnd_gen;
    int amount = 1;
    int length = 8;
    inline bool IsValidInt(int num);
    std::string m_mask;

public:
    char GenerateRandomChar(CHAR_TYPE char_type);
    char GenerateMaskChar(char symbol);
    void SetPasswordMask(const std::string& mask);
    void SetPasswordLength(int len);
    std::string GeneratePassword();
    PasswordGenerator() : rnd_gen(time(NULL))
    {
    }
};
