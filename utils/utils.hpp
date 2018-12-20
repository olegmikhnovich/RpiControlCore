#ifndef RPICONTROL_UTILS_H
#define RPICONTROL_UTILS_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>
#include <algorithm>
#include <cctype>
#include <locale>

class Utils {
public:
    static std::string exec(const char* cmd);
    static std::vector<std::string> split(const std::string &input, const std::string &regex);
    static void ltrim(std::string &s);
    static void rtrim(std::string &s);
    static void trim(std::string &s);
    static std::string ltrim_copy(std::string s);
    static std::string rtrim_copy(std::string s);
    static std::string trim_copy(std::string s);
};

#endif //RPICONTROL_UTILS_H
