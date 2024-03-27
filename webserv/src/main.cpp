#include <iostream>
#include "fstream"
#include "../include/define.hpp"
#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../verbose/verbose.hpp"

int main(int argc, char **argv)
{
    std::string config_file;
    if (argc > 1)
        config_file = argv[1];
    
    ServerConfig serverconfig;
    parsingSrvConf parse_config;

    parse_config.readConfigFile(config_file);// read the config file
    serverconfig = *parse_config.getServerConfig(); // get the server config

   
    void printSRVConfig(ServerConfig serverconfig);
   
    return 0;
}
