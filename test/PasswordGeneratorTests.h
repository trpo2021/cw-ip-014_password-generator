#pragma once
#define lest_FEATURE_AUTO_REGISTER 1
#include "PasswordGenerator.h"
#include "lest.hpp"
#include <algorithm>
#include <string>
#include <vector>

#define CASE(name) lest_CASE(specification, name)
static lest::tests specification;

void UniquePassTest(lest::env& lest_env)
{
    PasswordGenerator pgen;
    std::vector<std::string> passwords;
    passwords.reserve(10000);
    for (int a = 0; a < 10000; a++) {
        passwords.push_back(pgen.GeneratePassword());
    }
    std::sort(passwords.begin(), passwords.end());
    bool no_duplicates = std::adjacent_find(passwords.begin(), passwords.end())
            == passwords.end();
    EXPECT(no_duplicates == true);
}

CASE("Generate 10000 passwords and check for uniqueness")
{
    UniquePassTest(lest_env);
}

void CharGenValidTest(lest::env& lest_env)
{
    PasswordGenerator pgen;
    for (int a = 0; a < 100; a++) {
        EXPECT(std::isdigit(pgen.GenerateRandomChar(CHAR_TYPE::num_char)) != 0);
        EXPECT(std::isupper(pgen.GenerateRandomChar(CHAR_TYPE::up_char)) != 0);
        EXPECT(std::islower(pgen.GenerateRandomChar(CHAR_TYPE::low_char)) != 0);
    }
}

CASE("Check if char types match expected symbol type")
{
    CharGenValidTest(lest_env);
}

void PasswordGenParamsTest(lest::env& lest_env)
{
    PasswordGenerator pgen;
    pgen.SetPasswordLength(15);
    EXPECT(pgen.GeneratePassword().length() == 15); 
    // Length must be changed by mask
    pgen.SetPasswordMask("LU-NS");
    std::string mask_pass = pgen.GeneratePassword();
    EXPECT(mask_pass.length() == 6);
    // Check if correct chars are generated by mask
    EXPECT(std::islower(mask_pass[0]));
    EXPECT(std::isupper(mask_pass[1]));
    EXPECT(std::isdigit(mask_pass[3]));
}

CASE("Check SetPasswordMask/Length correctness")
{
    PasswordGenParamsTest(lest_env);
}

void PasswordMaskModeTest(lest::env& lest_env)
{
    PasswordGenerator pgen;
    pgen.SetPasswordMaskMode(ML_MODE::forward);
    
    std::vector<std::string> masks = {"N", "L", "U"};
    pgen.SetPasswordMasks(masks);

    std::string a=pgen.GeneratePassword();
    EXPECT(std::isdigit(a[0]));
    a=pgen.GeneratePassword();
    EXPECT(std::islower(a[0]));
    a=pgen.GeneratePassword();
    EXPECT(std::isupper(a[0]));

    pgen.SetPasswordMaskMode(ML_MODE::backward);
    a=pgen.GeneratePassword();
    EXPECT(std::isupper(a[0]));
    a=pgen.GeneratePassword();
    EXPECT(std::islower(a[0]));
    a=pgen.GeneratePassword();
    EXPECT(std::isdigit(a[0]));
}

CASE("PasswordMasksMode")
{
    PasswordMaskModeTest(lest_env);
}

