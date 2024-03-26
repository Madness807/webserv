#ifndef SERVER_HPP
#define SERVER_HPP

#include "ConfigParser.hpp"
#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

class Server
{
    private:
    int _opt;
    int _serverSocket; // listening socket
    fd_set _masterFd; // master file descriptor set
    int _newSocket;
    int _port;
    const char* _ipAdress;
    size_t _reading;
    struct sockaddr_in _addr;
    char _buffer[1024];
    std::string _test;
    //int _setsockopt;

    public:
        // constructeur et destructeur
        Server(const char* ipAdress, int port);
        Server();
        ~Server();
        Server(const Server &other);
        Server &operator=(const Server &other);

        int Init();
        int Run();
        // Méthodes///////////////////
        // GETTERS
        // SETTERS

    protected:
        virtual void onClientConnected(int clientSocket);
        virtual void onClientDisconnected(int clientSocket);
        virtual void onMessageReceived(int clientSocket, const char* message, int messageSize); // gestion de message recu d un client
        void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client
        void sendToAllClients(int sendingClientSocket, const char* message, int messageSize); // send message to all clients
};

#endif
