#include "../include/ConfigParser.hpp"

//Méthodes
//GETTERS
//SETTERS


// constructeur
parsingSrvConf::parsingSrvConf(){
}
// destructeur
parsingSrvConf::~parsingSrvConf() {
}


// lire le fichier de configuration
    // enregistre les valeurs dans une map
    // pour chaque clé, on a une valeur
    // exemple: "port" => "8080"
    //        "server_name" => "localhost"
    //        "root" => "/var/www/html"
    //        "index" => "index.html"
    //        "error_page" => "error.html"
    //        "location" => "/api"