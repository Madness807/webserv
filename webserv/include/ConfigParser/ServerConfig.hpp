#ifndef CONFIGSRVCONF_HPP
#define CONFIGSRVCONF_HPP

#include <string>
#include <map>
#include <list>

class ServerConfig{
    private:
        // Attributs Configuration de base du serveur
        std::string _server_name;
        std::string _ip;
        std::string _port;
        std::string _max_body_size;

        // Attributs Configuration des locations
        // MAP 1 : LocationConfig
        std::map<std::string, std::map<std::string, std::string> > locations_map;
        // MAP 2 : LocationConfig
        std::string _path;
        std::string _redirect;
        bool _directory_listing;

    public:
        // constructeur et destructeur
            ServerConfig();
            ~ServerConfig();

        // Méthodes Configuration de base du serveur///////////////
        // SETTERS
        void setServerName(std::string server_name);
        void setPort(std::string port);
        void setIp(std::string ip);
        void setMaxBodySize(std::string max_body_size);
        // GETTERS
        std::string getServerName();
        std::string getPort();
        std::string getIp();
        std::string getMaxBodySize();

        // Méthodes Configuration des locations///////////////////
        void addLocation(const std::string& path, const std::map<std::string, std::string>& locationConfig);
        // SETTERS
        void setPath(std::string path);
        void setMethods(std::vector<std::string> methods);
        void setRedirect(std::string redirect);
        void setDirectoryListing(bool directory_listing);
        // GETTERS
        std::map<std::string, std::string> getLocationConfig(const std::string& path);
        std::string getPath();
        std::vector<std::string> getMethods();
        std::string getRedirect();
        bool getDirectoryListing();

};

#endif
