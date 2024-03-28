#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../include/ConfigParser/LocationConfig.hpp"

#include <iostream>
#include <fstream>

//Méthodes
//GETTERS✅
ServerConfig* parsingSrvConf::getServerConfig(){
    return _serverConfig;
}
//SETTERS

void parsingSrvConf::readConfigFile(std::string filename) {
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }
    std::string line;
    LocationConfig location = LocationConfig();
    while (std::getline(configFile, line)) {
        if (line.find("server") != std::string::npos) {
            while (std::getline(configFile, line)) {
                if (line.find("end_config_server:") != std::string::npos) {
                    break;
                }
                else if (line.find("server_name") != std::string::npos) {
                    _serverConfig->setServerName(line.substr(line.find("server_name") + 12, line.find(":") - line.find("server_name") - 13));
                }
                else if (line.find("ip") != std::string::npos) {
                    _serverConfig->setIp(line.substr(line.find("ip") + 3, line.find(":") - line.find("ip") - 4));
                }
                else if (line.find("port") != std::string::npos) {
                    _serverConfig->setPort(line.substr(line.find("port") + 5, line.find(":") - line.find("port") - 6));
                }
                else if (line.find("max_body_size") != std::string::npos) {
                    _serverConfig->setMaxBodySize(line.substr(line.find("max_body_size") + 14, line.find(":") - line.find("max_body_size") - 15));
                }
                else if (line.find("default_file") != std::string::npos) {
                    _serverConfig->setDefaultFile(line.substr(line.find("default_file") + 12, line.find(":") - line.find("default_file") - 13));
                }
                else if (line.find("error_page") != std::string::npos) {
                    _serverConfig->setErrorPage(line.substr(line.find("error_page") + 11, line.find(":") - line.find("error_page") - 12));
                }
                else if (line.find("root") != std::string::npos) {
                    _serverConfig->setRoot(line.substr(line.find("root") + 6, line.find(":") - line.find("root") - 7));
                }//fin de la partie configuration de base du serveur
                else if (line.find("location_start") != std::string::npos)
                {
                    location = LocationConfig();
                }
                else if (line.find("path") != std::string::npos)
                {   
                    location.setPath(line.substr(line.find("path") + 6, line.find(":") - line.find("path") - 6));
                }
                if (line.find("redirect") != std::string::npos)
                {
                    location.setRedirect(line.substr(line.find("redirect") + 10, line.find(":") - line.find("redirect") - 10));
                }
                else if (line.find("methods") != std::string::npos)
                {
                    std::string methodsSubstr = line.substr(line.find("methods") + 9 , line.find(":") - line.find("methods") - 9);
                    methodsSubstr.erase(0, methodsSubstr.find_first_not_of(" "));
                    std::stringstream ss(methodsSubstr);
                    std::string method;
                    std::vector<std::string> methods;
                    
                    while (std::getline(ss, method, ','))
                    {
                        method.erase(0, method.find_first_not_of(" "));
                        method.erase(method.find_last_not_of(" ") + 1);
                        methods.push_back(method);
                    }
                    location.setMethods(methods);
                }
                else if (line.find("directory_listing") != std::string::npos)
                {
                    location.setDirectoryListing(false);
                }
                if (line.find("location_end") != std::string::npos)
                {
                    _serverConfig->addLocation(location.getPath() ,location);
                }
            }
        }
    }
    configFile.close();
}

// Constructeur✅
parsingSrvConf::parsingSrvConf() {
    _serverConfig = new ServerConfig();
}
// Constructeur par copie✅
parsingSrvConf::parsingSrvConf(const parsingSrvConf& other) {
    _serverConfig = new ServerConfig(*other._serverConfig);
}
// Destructeur✅
parsingSrvConf::~parsingSrvConf() {
    delete _serverConfig;
}
