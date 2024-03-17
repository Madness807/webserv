#ifndef SERVER_HPP
#define SERVER_HPP

#include "ConfigParser.hpp"
#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class Server
{
    private:
    int _opt;
    int _serverSocket;
    int _newSocket;
    int _port;
    int _ipAdress;
    size_t _reading;
    struct sockaddr_in _addr;
    std::string _buffer[1024];
    std::string _test;
    //int _setsockopt;

    public:
        // constructeur et destructeur
        Server(int ipAdress, int port);
        Server();
        ~Server();
        Server(const Server &other);
        Server &operator=(const Server &other);

        int Init();
        int Run();
        // Méthodes///////////////////
        // GETTERS
        // SETTERS

};

#endif
