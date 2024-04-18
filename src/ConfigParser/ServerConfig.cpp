#include "../include/ConfigParser/ServerConfig.hpp"
#include <string>
#include <cstdlib>

//##################################################################
//                          SETTERS                                #
//##################################################################
void ServerConfig::setServerName(std::string server_name) {
    server_name = trim(server_name);
    if (server_name.empty())
    {
        std::cerr << "Error: ServerName: empty server name" << std::endl;
        exit (1);
    }
    _server_name = server_name;
}
void ServerConfig::setIp(std::string ip) {
    ip = trim(ip);
    if (ip.empty())
    {
        std::cerr << "Error: IP: empty ip" << std::endl;
        exit (1);
    }
    _pair_ip_port.first = ip;
}
// void ServerConfig::setPort(std::string port) {
//     _pair_ip_port.second = std::stoi(port);
// }
void ServerConfig::setPort(std::string port) {
    port = trim(port);
    if (port.empty())
    {
        std::cerr << "Error: Port: empty port" << std::endl;
        exit (1);
    }
    _pair_ip_port.second = std::stoi(port);
}
void ServerConfig::setMaxBodySize(std::string max_body_size) {
    max_body_size = trim(max_body_size);
    if (max_body_size.empty())
    {
        std::cerr << "Error: MaxBodySize: empty max body size" << std::endl;
        exit (1);
    }
    _max_body_size = max_body_size;
}
void ServerConfig::setDefaultFile(std::string default_file) {
    default_file = trim(default_file);
    if (default_file.empty())
    {
        std::cerr << "Error: DefaultFile: empty default file" << std::endl;
        exit (1);
    }
    _default_file = default_file;
}
void ServerConfig::setErrorPage(std::string error_page) {
    error_page = trim(error_page);
    if (error_page.empty())
    {
        std::cerr << "Error: ErrorPage: empty error page" << std::endl;
        exit (1);
    }
    _error_page = error_page;
}
void ServerConfig::setRoot(std::string root) {
    root = trim(root);
    if (root.empty())
    {
        std::cerr << "Error: Root: empty root" << std::endl;
        exit (1);
    }
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
