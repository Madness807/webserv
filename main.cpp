#include "include/define.hpp"
#include "include/ConfigParser/ServerManager.hpp"
#include "include/TCPHandler/TCPHandler.hpp"
#include "include/verbose/verbose.hpp"
#include "include/Response/Response.hpp"

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

    // Print all servers config
    printSRVConfig(server_manager.getServerConfig("127.0.0.1", 8888));
    // printSRVConfig(server_manager.getServerConfig("127.0.0.1", 7777));
    // printSRVConfig(server_manager.getServerConfig("127.0.0.1", 5555));

    // test pour nrossel
    //ServerConfig *ServerConfig1 = server_manager.getServerConfig("127.0.0.1", 7777);

//##################################################################
//                          JDEFAYES                               #
//##################################################################
    TCPHandler tcpHandler;
    tcpHandler.setTabServers(server_manager);
    tcpHandler.initServer();
    tcpHandler.runServer();

    //commande pour voir les ports ouverts : watch "netstat -an | grep 127.0.0.1"
//##################################################################
//                          NROSSEL                                #
//##################################################################

    // std::string buffer = "GET /home.html?blabla=blabla+bla=bla+inc=inc HTTP/1.1\r\nHost: 120.0.0.1:8888\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nCookie: userId=12345; sessionId=67890\r\n\r\nbody: {bla}\r\n";
    // std::string buffer = "POST /upload HTTP/1.1 Host: exemple.com Content-Type: multipart/form-data; boundary=---12345 Content-Length: 123456 ---12345 Content-Disposition: form-data; name=\"texte\" Données du texte ici ---12345 Content-Disposition: form-data; name=]\"fichier\"; filename=\"image.jpg\" Content-Type: image/jpeg <Données binaires de l'image ici> ---12345--";

    // std::cout << "\n\n\n\n";
    //     Response response(buffer, *server_manager.getServerConfig("127.0.0.1", 8888));
    //     std::cout << response << std::endl;

    // // // std::cout << COLOR_RED << " -------------------- Test Leaks -------------------- \n\n" << COLOR_RESET;
    // // return 0;
}
// mettre buffer 1000 et boucler, strcat + pour former str finale.
