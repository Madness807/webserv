#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "ServerConfig.hpp"
#include "ConfigParser.hpp"

class ServerManager{
    private:
        std::vector<ServerConfig> _configs;

    public:
        // constructeur et destructeur
            ServerManager();
            ServerManager(std::string filename);
            ~ServerManager();

    // Méthodes pour gérer les configurations de serveur
            void addServerConfig(const std::string& ip, int port, const ServerConfig& config);
            void setServerConfig(std::string filename);
            void removeServerConfig(const std::string& ip, int port);
            ServerConfig* getServerConfig(const std::string& ip, int port);

    
    };

#endif

