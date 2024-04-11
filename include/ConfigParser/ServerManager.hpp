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
        std::map<std::pair<std::string, int>, ServerConfig> server_configs;

    public:
        // constructeur et destructeur
            ServerManager();
            ~ServerManager();

    // Méthodes pour gérer les configurations de serveur
    void addServerConfig(const std::string& ip, int port, const ServerConfig& config);
    ServerConfig* getServerConfig(const std::string& ip, int port);
    void removeServerConfig(const std::string& ip, int port);

};

#endif

