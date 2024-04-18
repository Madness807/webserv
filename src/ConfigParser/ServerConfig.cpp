#include "../include/ConfigParser/ServerConfig.hpp"
#include <string>
#include <cstdlib>

//##################################################################
//                          SETTERS                                #
//##################################################################
void ServerConfig::setServerName(std::string server_name) {
    _server_name = server_name;
}
void ServerConfig::setIp(std::string ip) {
    _pair_ip_port.first = ip;
}
// void ServerConfig::setPort(std::string port) {
//     _pair_ip_port.second = std::stoi(port);
// }
void ServerConfig::setPort(std::string port) {
    char* endptr; // Pointeur pour stocker la position après la conversion
    unsigned long value = strtoul(port.c_str(), &endptr, 10); // Convertir la chaîne en unsigned long

    if (*endptr != '\0') {
        // Gérer le cas où la conversion a échoué (par exemple, la chaîne contenait des caractères non numériques)
        // Vous pouvez afficher un message d'erreur ou prendre d'autres mesures appropriées ici.
    }

    _pair_ip_port.second = static_cast<int>(value); // Convertir unsigned long en int
}
void ServerConfig::setMaxBodySize(std::string max_body_size) {
    _max_body_size = max_body_size;
}
void ServerConfig::setDefaultFile(std::string default_file) {
    _default_file = default_file;
}
void ServerConfig::setErrorPage(std::string error_page) {
    _error_page = error_page;
}
void ServerConfig::setRoot(std::string root) {
    _root = root;
}
void ServerConfig::setLocations_map(std::map<std::string, LocationConfig> locations_map) {
    _locations_map = locations_map;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
std::string ServerConfig::getServerName() {
    return _server_name;
}
int ServerConfig::getPort() const {
    return _pair_ip_port.second;
}
std::string ServerConfig::getIp() const {
    return _pair_ip_port.first;
}

std::pair<std::string, int> ServerConfig::getPairIpPort() {
    return _pair_ip_port;
}

std::string ServerConfig::getMaxBodySize() {
    return _max_body_size;
}
std::string ServerConfig::getDefaultFile() {
    return _default_file;
}
std::string ServerConfig::getErrorPage() {
    return _error_page;
}
std::string ServerConfig::getRoot() {
    return _root;
}
LocationConfig ServerConfig::getLocationConfig(std::string path) {
    return _locations_map.at(path);
}
std::map<std::string, LocationConfig> &ServerConfig::getMapLocation(){
    return _locations_map;
}

//##################################################################
//                           Methodes                              #
//##################################################################
void ServerConfig::addLocation(const std::string& path, const LocationConfig& _locationConfig) {
    _locations_map[path] = _locationConfig;
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
ServerConfig::ServerConfig() {
    _server_name = "";
    _pair_ip_port.first = "";
    _pair_ip_port.second = 0;
    _max_body_size = "";
    _default_file = "";
    _error_page = "";
    _root = "";
}
ServerConfig::~ServerConfig() {
}
