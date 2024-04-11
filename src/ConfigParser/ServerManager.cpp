#include "../include/ConfigParser/ServerManager.hpp"

//##################################################################
//                          SETTERS                                #
//##################################################################



//##################################################################
//                          GETTERS                                #
//##################################################################
ServerConfig* ServerManager::getServerConfig(const std::string& ip, int port)
{
    // implémentation de la méthode getServerConfig en cpp98 sans auto
    std::map<std::pair<std::string, int>, ServerConfig>::iterator it = server_configs.find(std::make_pair(ip, port));
    if (it != server_configs.end()) {
        return &it->second;
    }
    return 0;
}

//##################################################################
//                           Methodes                              #
//##################################################################
void ServerManager::addServerConfig(const std::string& ip, int port, const ServerConfig& config) {
    // Ajoute une configuration de serveur
    server_configs[std::make_pair(ip, port)] = config;
}

void ServerManager::removeServerConfig(const std::string& ip, int port) {
    server_configs.erase(std::make_pair(ip, port));
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
ServerManager::ServerManager() {
    // Constructeur
}

ServerManager::~ServerManager() {
    // Destructeur
}

