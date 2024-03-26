#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"

#include <iostream>
#include <fstream>

//Méthodes
//GETTERS
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
    while (std::getline(configFile, line)) {
        if (line.find("server") != std::string::npos) {
            while (std::getline(configFile, line)) {
                if (line.find("end_config_server:") != std::string::npos) {
                    break;
                }
                if (line.find("server_name") != std::string::npos) {
                    _serverConfig->setServerName(line.substr(line.find("server_name") + 12, line.find(":") - line.find("server_name") - 13));
                }
                if (line.find("ip") != std::string::npos) {
                    _serverConfig->setIp(line.substr(line.find("ip") + 3, line.find(":") - line.find("ip") - 4));
                }
                if (line.find("port") != std::string::npos) {
                    _serverConfig->setPort(line.substr(line.find("port") + 5, line.find(":") - line.find("port") - 6));
                }
                if (line.find("max_body_size") != std::string::npos) {
                    _serverConfig->setMaxBodySize(line.substr(line.find("max_body_size") + 14, line.find(":") - line.find("max_body_size") - 15));
                }
                if (line.find("location_start") != std::string::npos) {
                    std::string path = line.substr(line.find("location") + 9, line.find(":") - line.find("location") - 10);
                    std::map<std::string, std::string> locationConfig;
                    while (std::getline(configFile, line)) {
                        if (line.find("location_end") != std::string::npos) {
                            break;
                        }
                        if (line.find("path") != std::string::npos) {
                            locationConfig["path"] = line.substr(line.find("path") + 5, line.find(":") - line.find("path") - 6);
                        }
                        if (line.find("redirect") != std::string::npos) {
                            locationConfig["redirect"] = line.substr(line.find("redirect") + 9, line.find(":") - line.find("redirect") - 10);
                        }
                        if (line.find("directory_listing") != std::string::npos) {
                            locationConfig["directory_listing"] = line.substr(line.find("directory_listing") + 18, line.find(":") - line.find("directory_listing") - 19);
                        }
                    }
                    _serverConfig->addLocation(path, locationConfig);
                }
            }
        }
    }
    configFile.close();
}

// Constructeur
parsingSrvConf::parsingSrvConf() {
    _serverConfig = new ServerConfig();
}
// Constructeur par copie
parsingSrvConf::parsingSrvConf(const parsingSrvConf& other) {
    _serverConfig = new ServerConfig(*other._serverConfig);
}
// Destructeur
parsingSrvConf::~parsingSrvConf() {
    delete _serverConfig;
}
