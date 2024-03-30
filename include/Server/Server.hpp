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
#include <fstream>

#define BUFFER_SIZE 1024
class Server
{
	private:

		int         			_opt;
		int        	 			_serverSocket; // listening socket
		fd_set	    			_masterFdRead;
		fd_set	    			_masterFdWrite;
		int         			_newSocket;
		int         			_port;
		std::string 			_ipAdress;
		size_t      			_reading;
		struct sockaddr_in 		_addr;
		char        			_buffer[BUFFER_SIZE];
		int 	   				_socketCount;
		std::string 			_file;
		std::string 			_response;

	public:

		Server(std::string ipAdress, int port);
		Server();
		virtual ~Server();
		Server(const Server &other);
		Server &operator=(const Server &other);

		int Init();
		int Run();

		std::string getFile() const;
		void setFile(std::string file);

		std::string getResponse() const;
		void setResponse(std::string response);

		int getServerSocket() const;
		void setServerSocket(int serverSocket);

		int getPort() const;

	protected:

		virtual void onClientConnected(int clientSocket);

		virtual void onClientDisconnected(int clientSocket);

		void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client

		void sendToAllClients(int sending_client, int max_sd, const char* message, int messageSize); // send message from a client to all clients

};

#endif
