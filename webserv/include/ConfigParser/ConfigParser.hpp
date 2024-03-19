#ifndef PARSINGSRVCONF_HPP
#define PARSINGSRVCONF_HPP

#include <string>
#include <map>
#include <list>
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

class parsingSrvConf{
    private:
    ServerConfig* _serverConfig;
    LocationConfig* _locationConfig;

    public:
        // Constructeur
            parsingSrvConf();
        // Constructeur par copie
            parsingSrvConf(const parsingSrvConf& other);
        // Destructeur
            ~parsingSrvConf();

        // Méthodes///////////////////
        void readConfigFile(std::string filename);

        // GETTERS
        ServerConfig* getServerConfig();
        LocationConfig* getLocationConfig();
        // SETTERS
};

#endif
