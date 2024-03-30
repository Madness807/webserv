#ifndef PARSINGSRVCONF_HPP
#define PARSINGSRVCONF_HPP

#include <string>
#include <map>
#include <list>
#include "ServerConfig.hpp"
#include <iostream>
#include <fstream>

class parsingSrvConf{
    private:
    std::vector<ServerConfig> _serverConfigs;

    public:
        // Constructeur
            parsingSrvConf();
        // Constructeur par copie
            parsingSrvConf(const parsingSrvConf& other);
        // Destructeur
            ~parsingSrvConf();

        // Méthodes///////////////////
        void readConfigFile(std::string filename);
        void parseServerConfig(std::string line);
        LocationConfig parseLocationConfig(std::string line, LocationConfig& location);


        // GETTERS
        ServerConfig* getServerConfig(const std::string& ip, int port);
        // SETTERS
};

#endif


//todo modidfier le parsing pour quil prenne en compte les multiples server
//modifier la boucle du parsing pour quil prenne en compte les multiples server
//ajouter un getter pour recuperer un serverconfig en fonction de l'ip et du port
//ajouter un getter pour recuperer un locationconfig en fonction du path
//ajouter un getter pour recuperer un locationconfig en fonction du path et du serverconfig