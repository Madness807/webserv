#include "../include/ConfigParser/ServerConfig.hpp"

//##################################################################
//                          SETTERS                                #
//##################################################################
void ServerConfig::setServerName(std::string server_name) {
    _server_name = server_name;
}
void ServerConfig::setPort(std::string port) {
    //conversion string en int
    _pair_ip_port.second = std::stoi(port);
}
void ServerConfig::setIp(std::string ip) {
    _pair_ip_port.first = ip;
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
int ServerConfig::getPort() {
    return _pair_ip_port.second;
}
std::string ServerConfig::getIp() {
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
