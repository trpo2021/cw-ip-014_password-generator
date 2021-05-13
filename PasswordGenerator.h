#pragma once
#include <iostream>
#include <random>

enum class CHAR_TYPE { UP_LETTER, LOW_LETTER, NUM_LETTER, SPEC_SYMBOL };

class PasswordGenerator {
private:
    std::mt19937_64 rnd_gen;
    int amount = 1;
    int length = 8;
    inline bool IsValidInt(int num);
    char GenerateRandomChar(CHAR_TYPE char_type);

public:
    void SetPasswordsLength(int len);
    std::string GeneratePassword();
    PasswordGenerator() : rnd_gen(time(NULL))
    {
    }
};
