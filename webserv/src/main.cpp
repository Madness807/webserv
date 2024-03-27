#include <iostream>
#include "fstream"
#include "../include/define.hpp"
#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"

int main(int argc, char **argv)
{
    std::string config_file;
    if (argc > 1)
        config_file = argv[1];
    
    ServerConfig serverconfig;
    parsingSrvConf parse_config;

    parse_config.readConfigFile(config_file);// read the config file
    serverconfig = *parse_config.getServerConfig(); // get the server config

    // TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION TEST IMPRESSION//
    //Print the server config
    std::cout << "" << std::endl;
    std::cout << "\033[31mRESULTAT DU PARSING DU FICHIER DE CONFIGURATION DU SERVEUR\033[0m" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "\033[31mSERVERCONFIG-------------------------\033[0m" << std::endl;
    std::cout << "Server Name: " << serverconfig.getServerName() << std::endl;
    std::cout << "Server IP: " << serverconfig.getIp() << std::endl;
    std::cout << "Server Port: " << serverconfig.getPort() << std::endl;
    std::cout << "Server Max Body Size: " << serverconfig.getMaxBodySize() << std::endl;
    std::cout << "Server Default File: " << serverconfig.getDefaultFile() << std::endl;
    std::cout << "Server Error Page: " << serverconfig.getErrorPage() << std::endl;
    std::cout << "Server Root: " << serverconfig.getRoot() << std::endl;

    //Print the location config
    std::cout << "" << std::endl;
    std::cout << "\033[31mLOCATIONCONFIG-------------------------\033[0m" << std::endl;

    std::cout << "Path: " << serverconfig.getLocationConfig("/").getPath() << std::endl;
    std::cout << "Redirection: " << serverconfig.getLocationConfig("/").getRedirect() << std::endl;
    std::cout << "DirectoryListing: " << serverconfig.getLocationConfig("/").getDirectoryListing() << std::endl;
   
    return 0;
}
