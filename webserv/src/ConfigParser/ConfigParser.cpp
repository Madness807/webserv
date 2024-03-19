#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../include/ConfigParser/LocationConfig.hpp"

#include <iostream>
#include <fstream>

//Méthodes
//GETTERS
ServerConfig* parsingSrvConf::getServerConfig(){
    return _serverConfig;
}
LocationConfig* parsingSrvConf::getLocationConfig(){
    return _locationConfig;
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
                    while (std::getline(configFile, line)) {
                        if (line.find("location_end") != std::string::npos) {
                            break;
                        }
                        if (line.find("path") != std::string::npos) {
                            _locationConfig->setPath(line.substr(line.find("path") + 5, line.find(":") - line.find("path") - 6));
                        }
                        if (line.find("methods") != std::string::npos) {
                            std::string methods = line.substr(line.find("methods") + 8, line.find(":") - line.find("methods") - 9);
                            std::vector<std::string> methodsVector;
                            std::string delimiter = " ";
                            size_t pos = 0;
                            std::string token;
                            while ((pos = methods.find(delimiter)) != std::string::npos) {
                                token = methods.substr(0, pos);
                                methodsVector.push_back(token);
                                methods.erase(0, pos + delimiter.length());
                            }
                            methodsVector.push_back(methods);
                            _locationConfig->setMethods(methodsVector);
                        }
                        if (line.find("redirect") != std::string::npos) {
                            _locationConfig->setRedirect(line.substr(line.find("redirect") + 9, line.find(":") - line.find("redirect") - 10));
                        }
                    }
                    _serverConfig->addLocation(_locationConfig);
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
    _locationConfig = new LocationConfig(*other._locationConfig);
}
// Destructeur
parsingSrvConf::~parsingSrvConf() {
    delete _serverConfig;
}
