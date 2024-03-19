#include "../include/ConfigParser/ServerConfig.hpp"

//Méthodes
//SETTERS
void ServerConfig::setServerName(std::string server_name) {
    _server_name = server_name;
}
void ServerConfig::setPort(std::string port) {
    _port = port;
}
void ServerConfig::setIp(std::string ip) {
    _ip = ip;
}
void ServerConfig::setMaxBodySize(std::string max_body_size) {
    _max_body_size = max_body_size;
}
//GETTERS
std::string ServerConfig::getServerName() {
    return _server_name;
}
std::string ServerConfig::getPort() {
    return _port;
}
std::string ServerConfig::getIp() {
    return _ip;
}
std::string ServerConfig::getMaxBodySize() {
    return _max_body_size;
}

// constructeur
ServerConfig::ServerConfig() {
}
// destructeur
ServerConfig::~ServerConfig() {
}
