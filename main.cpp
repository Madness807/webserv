#include <iostream>
#include "fstream"
#include "include/define.hpp"
#include "include/ConfigParser/ConfigParser.hpp"
#include "include/ConfigParser/ServerConfig.hpp"
#include "include/verbose/verbose.hpp"
#include "include/Server/Server.hpp"
#include "include/client/Client.hpp"

int main(int argc, char **argv)
{
    std::string config_file;
    if (argc > 1)
        config_file = argv[1];

//##################################################################
//                          JOTERRET                               #
//##################################################################

    ServerConfig serverconfig;
    parsingSrvConf parse_config;

    parse_config.readConfigFile(config_file);// read the config file
    serverconfig = *parse_config.getServerConfig(); // get the server config

    printSRVConfig(serverconfig);

    


//##################################################################
//                          JDEFAYES                               #
//##################################################################

     Server test(serverconfig.getIp(), serverconfig.getPort());
     if (test.Init() < 0)
         return -1;
    test.Run();
    std::cout << "Server is running" << std::endl;

//##################################################################
//                          NROSSEL                                #
//##################################################################

    return 0;
}
