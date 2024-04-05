#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "ServerConfig.hpp"

class ServerManager{
    private:
        // Attributs
        std::string server_name;
        std::map<std::string, ServerConfig> server_configs;

    public:
        // constructeur et destructeur
            ServerManager();
            ~ServerManager();

    // Méthodes pour gérer les configurations de serveur
    void addServerConfig(const std::string& serverName, const ServerConfig& config);

    ServerConfig* getServerConfig(const std::string& serverName);

    void removeServerConfig(const std::string& serverName);

};

#endif
