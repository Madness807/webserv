#include <iostream>
#include "fstream"
#include "../include/define.hpp"

int main()
{
    std::cout << COLOR_GREEN << "Hello, World!" << std::endl;

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