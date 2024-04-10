#include "../include/ConfigParser/ServerManager.hpp"

//##################################################################
//                          SETTERS                                #
//##################################################################



//##################################################################
//                          GETTERS                                #
//##################################################################

//##################################################################
//                           Methodes                              #
//##################################################################
void ServerManager::addServerConfig(const std::string& serverName, const ServerConfig& config) {
    server_configs[serverName] = config;
}
void ServerManager::removeServerConfig(const std::string& serverName) {
    server_configs.erase(serverName);
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

