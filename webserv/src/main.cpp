#include <iostream>
#include "fstream"
#include "../include/define.hpp"

int main(int argc, char **argv)
{
    std::string config_file = "./config/webserv.conf";
    if (argc > 1)
        config_file = argv[1];
    

    // initialisation de la configuration
    // instanciation de la classe parsingSrvConf
    // gestion des signaux pour arret propre du serveur

    std::cout << "config_file: " << config_file << std::endl;
    std::ifstream file(config_file);
    
    return 0;
}