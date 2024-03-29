#include <iostream>
#include "fstream"
#include "include/define.hpp"
#include "include/ConfigParser/ConfigParser.hpp"
#include "include/ConfigParser/ServerConfig.hpp"
#include "include/verbose/verbose.hpp"
#include "include/Server/Server.hpp"
#include "include/client/Client.hpp"
#include "include/Request/Request.hpp"

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
    //test.Run();
    std::cout << "Server is running" << std::endl;


//##################################################################
//                          NROSSEL                                #
//##################################################################

    std::string buffer = "GET /index.html?blabla=blabla+bla=bla+inc=inc HTTP/1.1\r\nHost: example.com:8080\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nCookie: userId=12345; sessionId=67890\r\n\r\nbody: {bla}\r\n";

        Request test_requette(buffer);
        std::cout << test_requette << std::endl;

    return 0;
}
