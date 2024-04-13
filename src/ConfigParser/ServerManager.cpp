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
        std::cerr << "\033[1;31mError: GetServerConfig: Server not found: Bad ip or Bad Port\033[0m" << std::endl;
        exit (1);
        return NULL;
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

