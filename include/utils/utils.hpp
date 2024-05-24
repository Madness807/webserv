#ifndef UTILS_HPP
#define UTILS_HPP

#include "../define.hpp"

std::string trim(const std::string& str);
std::string getCurrentTimestamp();
int	pathIsFile(const std::string &path);
int hasWritePermission(const std::string &path);
int ft_atoi(std::string str);
int isspace(char c);

#endif