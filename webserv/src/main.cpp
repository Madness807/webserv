#include <iostream>
#include "fstream"
#include "../include/define.hpp"
#include "../include/Client.hpp"
#include "../include/Server.hpp"


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    // Client2 mcc("0.0.0.0", 8080);
    // if (mcc.Init() == -1)
    //     return -1;
    // mcc.Run();
    Server test("0.0.0.0", 8080);
    if (test.Init() == -1)
        return -1;
    test.Run();
    // std::string config_file = "./config/webserv.conf";
    // if (argc > 1)
    //     config_file = argv[1];
  //  Client test_c();
    //Server test_s();

    // initialisation de la configuration
    // instanciation de la classe parsingSrvConf
    // gestion des signaux pour arret propre du serveur

   // std::cout << "config_file: " << config_file << std::endl;

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
