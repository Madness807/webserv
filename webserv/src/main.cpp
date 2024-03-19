#include <iostream>
#include "fstream"
#include "../include/define.hpp"
#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../include/ConfigParser/LocationConfig.hpp"

int main(int argc, char **argv)
{
    std::string config_file;
    if (argc > 1)
        config_file = argv[1];
    

    ServerConfig serverconfig;
    LocationConfig    locationconfig;
    parsingSrvConf parse_config;

    parse_config.readConfigFile(config_file);// read the config file
    serverconfig = *parse_config.getServerConfig(); // get the server config
    locationconfig = *parse_config.getLocationConfig(); // get the location config

    // TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION//
    //Print the server config
    std::cout << "" << std::endl;
    std::cout << "\033[31mSERVERCONFIG-------------------------\033[0m" << std::endl;
    std::cout << "Server Name: " << serverconfig.getServerName() << std::endl;
    std::cout << "Server IP: " << serverconfig.getIp() << std::endl;
    std::cout << "Server Port: " << serverconfig.getPort() << std::endl;
    std::cout << "Server Max Body Size: " << serverconfig.getMaxBodySize() << std::endl;

    //Print the location config
    std::cout << "" << std::endl;
    std::cout << "\033[31mLOCATIONCONFIG-------------------------\033[0m" << std::endl;

    // TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION//
    std::cout << "Location Path: " << locationconfig.getPath() << std::endl;
    std::cout << "Location Methods: ";
    std::vector<std::string> methods = locationconfig.getMethods();
    for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "Location Redirect: " << locationconfig.getRedirect() << std::endl;
    std::cout << "" << std::endl;
    // TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION//
    
    return 0;
}
