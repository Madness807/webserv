#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ConfigParser.hpp"
#include "Connection.hpp"
#include "ConfigParser.hpp"
#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
class Client
{
    private:
        int _socketClient;
        int _opt;
        int _serverPort;
        int _serverIpAdress;
        size_t _reading;
        std::string _buffer[1024];
        struct sockaddr_in _addrServer;
        std::string _testClient;

    public:
        // constructeur et destructeur
        Client();
        Client(int ipAdress, int port);
        ~Client();
        Client(const Client &other);
        Client &operator=(const Client &other);

        int Init();
        int Run();

        // Méthodes///////////////////
        // GETTERS
        // SETTERS

};

#endif
