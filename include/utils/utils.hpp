#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <cctype>
#include <locale>
#include <ctime>

std::string trim(const std::string& str);
std::string getCurrentTimestamp();
std::string intToString(int value);

#endif