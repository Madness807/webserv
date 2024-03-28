#ifndef PARSINGSRVCONF_HPP
#define PARSINGSRVCONF_HPP

#include <string>
#include <map>
#include <list>
#include "ServerConfig.hpp"

class parsingSrvConf{
    private:
    ServerConfig* _serverConfig;

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
        // SETTERS
};

#endif
