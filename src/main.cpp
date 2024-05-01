#include "../include/define.hpp"
#include "../include/ConfigParser/ServerManager.hpp"
#include "../include/Connection/TCPHandler.hpp"
#include "../include/Response/Response.hpp"
#include "../include/verbose/verbose.hpp"

int main(int argc, char **argv)
{
    std::string config_file;
    if (argc > 1){
        config_file = argv[1];
    }
    else {
        std::cout << "USE OF DEFAULT CONFIG FILE" << std::endl;
        config_file = "config/default.conf";
    }
ServerManager server_manager(config_file);
        printAllSrvConfig(&server_manager);
        std::vector<int> clients;
        TCPHandler tcpHandler(clients);
        tcpHandler.setTabServers(server_manager);
        tcpHandler.initServer();
        tcpHandler.runServer();
}
