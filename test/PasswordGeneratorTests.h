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
    bool res = std::adjacent_find(passwords.begin(), passwords.end())
            == passwords.end();
    EXPECT(res == true);
}

CASE("Generate 10000 passwords and check for uniquness")
{
    UniquePassTest(lest_env);
}
