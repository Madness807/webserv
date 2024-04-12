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
		int         			_newSocket;
		int         			_port;
		std::string 			_ipAdress;
		ssize_t      			_reading;
		struct sockaddr_in 		_addr;
		std::string        		_buffer;
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

		std::string getFile() const;
		void setFile(std::string file);

		std::string getResponse() const;
		void setResponse(std::string response);

		int getServerSocket() const;
		void setServerSocket(int serverSocket);

		int getPort() const;

		std::string getIpAdress() const;

		std::string getBuffer() const;

		void setReading(int reading);
		int getReading() const;

		void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client


	protected:

		virtual void onClientConnected(int clientSocket);

		virtual void onClientDisconnected(int clientSocket);
};

#endif
