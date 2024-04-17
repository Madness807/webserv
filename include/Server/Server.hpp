#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../include/ConfigParser/ConfigParser.hpp"
#include "../../include/Connection/Connection.hpp"
#include "../ConfigParser/ServerConfig.hpp"
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
		int         			_newSocket;
		int         			_port;
		std::string 			_ipAdress;
		ssize_t      			_reading;
		struct sockaddr_in 		_addr;
		std::string        		_buffer;
		int 	   				_socketCount;
		std::string 			_file;
		std::string 			_response;
		std::string				_request;
		ServerConfig			_serverConfig;

	protected:

		virtual void onClientConnected(int clientSocket);
		virtual void onClientDisconnected(int clientSocket);

	public:
		// constructeur et destructeur
		Server();
		Server(std::string ipAdress, int port, ServerConfig conf);
		virtual ~Server();

		// constructeur par copie et operateur d'affectation
		Server(const Server &other);
		Server &operator=(const Server &other);

		// SETTERS
		void setFile(std::string file);
		void setResponse(std::string response);
		void setServerSocket(int serverSocket);
		void setReading(int reading);

		// GETTERS
		std::string getResponse() const;
		int getServerSocket() const;
		std::string getFile() const;
		int getPort() const;
		std::string getIpAdress() const;
		std::string getBuffer() const;
		int getReading() const;

		// Méthodes
		int Init();
		void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client

};

#endif
