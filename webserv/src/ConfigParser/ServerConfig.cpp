#include "../include/ConfigParser/ServerConfig.hpp"

//SETTERS////////////////////////////////////////////////////////////
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
void ServerConfig::setPath(std::string path){
    _path = path;
}
void ServerConfig::setRedirect(std::string redirect){
    _redirect = redirect;
}

//GETTERS////////////////////////////////////////////////////////////
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
std::string ServerConfig::getPath(){
    return _path;
}
std::string ServerConfig::getRedirect(){
    return _redirect;
}

//Méthodes////////////////////////////////////////////////////////////
void ServerConfig::addLocation(const std::string& path, const std::map<std::string, std::string>& locationConfig) {
    locations_map[path] = locationConfig;
}
// Constructeur et destructeur////////////////////////////////////////
// constructeur
ServerConfig::ServerConfig() {
}
// destructeur
ServerConfig::~ServerConfig() {
}
