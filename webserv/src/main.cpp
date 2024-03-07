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

    // lire le fichier de configuration
    // enregistre les valeurs dans une map
    // pour chaque clé, on a une valeur
    // exemple: "port" => "8080"
    //        "server_name" => "localhost"
    //        "root" => "/var/www/html"
    //        "index" => "index.html"
    //        "error_page" => "error.html"
    //        "location" => "/api"
    // 

    
    return 0;
}