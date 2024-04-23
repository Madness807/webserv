#ifndef PARSINGSRVCONF_HPP
#define PARSINGSRVCONF_HPP

#include "ServerConfig.hpp"
#include "../utils/utils.hpp"
#include "../define.hpp"
// #include <string>
// #include <map>
// #include <list>
// #include <iostream>
// #include <fstream>

class parsingSrvConf{
    public:
        // Constructeur
            parsingSrvConf();
        // Constructeur par copie
            parsingSrvConf(const parsingSrvConf& other);
        // Destructeur
            ~parsingSrvConf();

        // Méthodes///////////////////
        std::vector<ServerConfig> readConfigFile(std::string filename);
        void parseServerConfig(std::string line, ServerConfig& serverConfig);
        LocationConfig parseLocationConfig(std::string line, LocationConfig& location);

        // GETTERS
        ServerConfig* getServerConfig(const std::string& ip, int port);
        // SETTERS

};

#endif

// todo faire la gestion d erreur pour les fichiers de config
// verifier que j ai au moin l adresse ip et le port
// verifier que j ai au moin un path
