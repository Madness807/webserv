#ifndef CONFIGSRVCONF_HPP
#define CONFIGSRVCONF_HPP

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "LocationConfig.hpp"

class ServerConfig{
    private:
        // Attributs Configuration de base du serveur✅
        std::string _server_name;
        std::string _ip;
        int _port;
        std::string _max_body_size;
        std::string _default_file;
        std::string _error_page;
        std::string _root;
        std::map<std::string, LocationConfig > _locations_map;

    public:
        // constructeur et destructeur
            ServerConfig();
            ~ServerConfig();

        // Méthodes Configuration de base du serveur///////////////
        // SETTERS
        void setServerName(std::string server_name);
        void setPort(std::string _port);
        void setIp(std::string ip);
        void setMaxBodySize(std::string max_body_size);
        void setDefaultFile(std::string default_file);
        void setErrorPage(std::string error_page);
        void setRoot(std::string root);
        void setLocations_map(std::map<std::string, LocationConfig > _locations_map);

        // GETTERS
        std::string getServerName();
        int getPort();
        std::string getIp();
        std::string getMaxBodySize();
        std::string getDefaultFile();
        std::string getErrorPage();
        std::string getRoot();
        LocationConfig getLocationConfig(std::string path);

        // Méthodes
        void addLocation(const std::string& path, const LocationConfig& _locationConfig);
    
};

#endif
