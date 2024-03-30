#include <iostream>
#include "fstream"
#include "include/define.hpp"
#include "include/ConfigParser/ConfigParser.hpp"
#include "include/ConfigParser/ServerConfig.hpp"
#include "include/verbose/verbose.hpp"
#include "include/Server/Server.hpp"
#include "include/client/Client.hpp"
#include "include/Request/Request.hpp"
#include "include/TCPHandler/TCPHandler.hpp"

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
    TCPHandler tcpHandler;

    tcpHandler.setTabServers(2); // nombre de server a mettre en parametre
    std::cout << "serverSocket[0] : " << tcpHandler.getTabServers()[0].getPort() << std::endl;
     std::cout << "serverSocket[1] : " << tcpHandler.getTabServers()[1].getPort() << std::endl;
    tcpHandler.initServer(2); // nombre de server a mettre en parametre
    //std::vector<Server> servers(2);
    //Server servers[2](); // use getNbOfServer() to get the number of servers
    // servers[0] = Server("127.0.0.1", 8888);
    // servers[1] = Server("127.0.0.1", 8080);

    // servers[1].setFile("/Users/jdefayes/documents/git/Cursus/webserv/website/sitetest.html");
    // servers[0].setFile("/Users/jdefayes/documents/git/Cursus/webserv/website/MITSUBISHI-Galant-2.5-V6-24V-Edition-Kombi-215000km-Benziner-Automat-2498ccm-161PS-6Zylinder-1580kg-104L-930x620.jpg");

    // std::cout << "file[0] :" << servers[0].getFile() << std::endl;
    // std::cout << "file[1] :" << servers[1].getFile() << std::endl;

    // servers[1].setResponse("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    // servers[0].setResponse("HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n");


    // Server test(serverconfig.getIp(), serverconfig.getPort());
    // for (int i = 0; i < 2; i++)
    // {
    //     if (servers[i].initServer() < 0)
    //         return -1;
    //     //servers[i].Run();
    // }
    //  if (test.Init() < 0)
    //      return -1;
    // test.Run();
    std::cout << "Server is running" << std::endl;


//##################################################################
//                          NROSSEL                                #
//##################################################################

    std::string buffer = "GET /index.html?blabla=blabla+bla=bla+inc=inc HTTP/1.1\r\nHost: example.com:8080\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nCookie: userId=12345; sessionId=67890\r\n\r\nbody: {bla}\r\n";

        Request test_requette(buffer);
        std::cout << test_requette << std::endl;

    return 0;
}


// mettre buffer 1000 et boucler, strcat + pour former str finale.
