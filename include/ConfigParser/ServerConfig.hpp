#ifndef CONFIGSRVCONF_HPP
#define CONFIGSRVCONF_HPP

#include "../define.hpp"
#include "LocationConfig.hpp"
#include "../utils/utils.hpp"

class ServerConfig{
    private:
        // Attributs Configuration de base du serveur
        std::string _server_name;
        std::string _max_body_size;
        std::string _index;
        std::string _error_page;
        std::string _root;
        std::pair<std::string, int> _pair_ip_port;
        std::map<std::string, LocationConfig > _locations_map;

    public:
        // constructeur et destructeur
            ServerConfig();
            ~ServerConfig();

        // SETTERS
        void setServerName(std::string server_name);
        void setPort(std::string _port);
        void setIp(std::string ip);
        void setMaxBodySize(std::string max_body_size);
        void setIndex(std::string index);
        void setErrorPage(std::string error_page);
        void setRoot(std::string root);
        void setLocations_map(std::map<std::string, LocationConfig > _locations_map);

        // GETTERS
        std::string getServerName() const;
        int getPort() const;
        std::string getIp() const;
        std::string getMaxBodySize() const;
        std::string getIndex() const;
        std::string getErrorPage() const;
        std::string getRoot() const;
        std::pair<std::string, int> getPairIpPort();
        
        LocationConfig getLocationConfig(std::string path);
        const std::map<std::string, LocationConfig> &getMapLocation() const;

        // Méthodes
        void addLocation(const std::string& path, const LocationConfig& _locationConfig);
        void checkServerConfig();

};

#endif
