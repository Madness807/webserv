#include "../include/ConfigParser/ServerManager.hpp"

//##################################################################
//                          GETTERS                                #
//##################################################################
void ServerManager::setServerConfig(std::string filename)
{
    parsingSrvConf parsing;
    this->_configs = parsing.readConfigFile(filename);
}

//##################################################################
//                           Methodes                              #
//##################################################################

    ServerConfig* ServerManager::getServerConfig(const std::string& ip, int port)
    {
        std::vector<ServerConfig>::iterator it;
        for (it = this->_configs.begin(); it != this->_configs.end(); it++)
        {
            if (it->getIp() == ip && it->getPort() == port)
                return &(*it);
        }
        return NULL;
    }

const std::vector<ServerConfig> ServerManager::getServerConfig() const
{
    return  this->_configs;
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
ServerManager::ServerManager() {
    // Constructeur
}
ServerManager::ServerManager(std::string filename) {
    parsingSrvConf parsing;
    this->_configs = parsing.readConfigFile(filename);
}

ServerManager::~ServerManager() {
    // Destructeur
}

