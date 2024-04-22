#ifndef PARSINGSRVCONF_HPP
#define PARSINGSRVCONF_HPP

#include "ServerConfig.hpp"
#include "../utils/utils.hpp"
#include "../define.hpp"

class parsingSrvConf{
    public:
        // Constructeur
            parsingSrvConf();
        // Constructeur par copie
            parsingSrvConf(const parsingSrvConf& other);
        // Destructeur
            ~parsingSrvConf();

        std::set<int> usedPorts;//liste des ports utilisés
        
        // Méthodes///////////////////
        std::vector<ServerConfig> readConfigFile(std::string filename);
        void parseServerConfig(std::string line, ServerConfig& serverConfig);
        LocationConfig parseLocationConfig(std::string line, LocationConfig& location);

        // GETTERS
        ServerConfig* getServerConfig(const std::string& ip, int port);
        // SETTERS

};

#endif

