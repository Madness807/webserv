#ifndef PARSINGSRVCONF_HPP
#define PARSINGSRVCONF_HPP

#include <string>
#include <map>
#include <list>
#include "ServerConfig.hpp"
#include "ServerManager.hpp"
#include <iostream>
#include <fstream>

class parsingSrvConf{
    private:
        ServerManager _serverManager;

    public:
        // Constructeur
            parsingSrvConf();
        // Constructeur par copie
            parsingSrvConf(const parsingSrvConf& other);
        // Destructeur
            ~parsingSrvConf();

        // Méthodes///////////////////
        void readConfigFile(std::string filename);
        void parseServerConfig(std::string line, ServerConfig& serverConfig);
        LocationConfig parseLocationConfig(std::string line, LocationConfig& location);

        // GETTERS
        ServerConfig* getServerConfig(const std::string& ip, int port);
        ServerConfig* getServerManager(ServerManager& serverManager);
        // SETTERS

};

#endif

//todo modidfier le parsing pour quil prenne en compte les multiples server
//modifier la boucle du parsing pour qu'il prenne en compte les multiples server
//ajouter un getter pour recuperer un serverconfig en fonction de l'ip et du port
//ajouter un getter pour recuperer un locationconfig en fonction du path
//ajouter un getter pour recuperer un locationconfig en fonction du path et du serverconfig

// todo faire la gestion d erreur pour les fichiers de config
// verifier que j ai au moin l adresse ip et le port
// verifier que j ai au moin un path
