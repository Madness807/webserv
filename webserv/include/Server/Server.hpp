#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../include/ConfigParser/ConfigParser.hpp"
#include "../../include/Connection/Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

class Server
{
	private:

		int         _opt;
		int         _serverSocket; // listening socket
		fd_set	    _masterFdRead;
		fd_set	    _masterFdWrite;
		int         _newSocket;
		int         _port;
		const char* _ipAdress;
		size_t      _reading;
		struct      sockaddr_in _addr;
		char        _buffer[4096];
		int 	   _socketCount;

	public:

		Server(const char* ipAdress, int port);
		Server();
		~Server();
		Server(const Server &other);
		Server &operator=(const Server &other);

		int Init();
		int Run();

	protected:

		virtual void onClientConnected(int clientSocket);

		virtual void onClientDisconnected(int clientSocket);

		void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client

		void sendToAllClients(int sending_client, int max_sd, const char* message, int messageSize); // send message from a client to all clients

};

#endif
