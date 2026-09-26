#pragma once

#include <string>

class EditDistance {
public:
    static int calculate(const std::string& a, const std::string& b);
};