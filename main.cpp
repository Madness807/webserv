#include <iostream>
#include "fstream"
#include "include/define.hpp"
#include "include/ConfigParser/ServerManager.hpp"
#include "include/ConfigParser/ServerConfig.hpp"
#include "include/verbose/verbose.hpp"
#include "include/Server/Server.hpp"
#include "include/client/Client.hpp"
#include "include/Request/Request.hpp"
#include "include/Response/Response.hpp"
#include "include/TCPHandler/TCPHandler.hpp"

int main(int argc, char **argv)
{
    std::string config_file;
    if (argc > 1)
        config_file = argv[1];
    else {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

//##################################################################
//                          JOTERRET                               #
//##################################################################

    ServerManager server_manager(config_file);

    //printSRVConfig(server_manager.getServerConfig("127.0.0.1", 8888));
    //printSRVConfig(server_manager.getServerConfig("127.0.0.1", 7777));


    ServerConfig *ServerConfig1 = server_manager.getServerConfig("127.0.0.1", 8888);

    // std::cout << ServerConfig1->getMaxBodySize() << std::endl;
    // std::cout << ServerConfig1->getDefaultFile() << std::endl;
    // std::cout << ServerConfig1->getErrorPage() << std::endl;
    // std::cout << ServerConfig1->getRoot() << std::endl;
    // std::cout << ServerConfig1->getServerName() << std::endl;
    // std::cout << ServerConfig1->getPairIpPort().first << std::endl;
    // std::cout << ServerConfig1->getPairIpPort().second << std::endl;

//##################################################################
//                          JDEFAYES                               #
//##################################################################
    TCPHandler tcpHandler;
    //_serverManager = &server_manager;
    //  Server test_server(serverconfig.getIp(), serverconfig.getPort());
    //  if (test_server.Init() < 0)
    //      return -1;
    tcpHandler.setTabServers(server_manager);
    //tcpHandler.setTabServers(2); // nombre de server a mettre en parametre
    tcpHandler.initServer(tcpHandler.getNbOfServer()); // nombre de server a mettre en parametre
    // tcpHandler.runServer();

    std::cout << "Server is running" << std::endl;


    // Server test(serverconfig->getIp(), serverconfig->getPort());
    //  if (test.Init() < 0)
    //      return -1;
    // test.Run();
    // std::cout << "Server is running" << std::endl;

//##################################################################
//                          NROSSEL                                #
//##################################################################

    std::string buffer = "GET /index.html?blabla=blabla+bla=bla+inc=inc HTTP/1.1\r\nHost: 120.0.0.1:8888\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nCookie: userId=12345; sessionId=67890\r\n\r\nbody: {bla}\r\n";

    std::cout << "\n\n\n\n";
        Response response(buffer, *ServerConfig1);
        std::cout << response << std::endl;
    //     Request test_requette(buffer);
    //     std::cout << test_requette << std::endl;

    // // std::cout << COLOR_RED << " -------------------- Test Leaks -------------------- \n\n" << COLOR_RESET;
    // return 0;
}


// mettre buffer 1000 et boucler, strcat + pour former str finale.
