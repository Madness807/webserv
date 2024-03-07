#include <iostream>
#include "fstream"
#include "../include/define.hpp"

int main(int argc, char **argv)
{
    std::string config_file = "./config/webserv.conf";
    if (argc > 1)
        config_file = argv[1];
    
    
    std::cout << COLOR_GREEN << "Hello, World!" << std::endl;


    return 0;
}