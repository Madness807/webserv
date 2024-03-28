#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Connection/Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

class Client
{
	private:
		int _socketClient;
		std::string _clientRequete;
		std::string _clientReponse;
		std::string _buffer[1024];

	public:
		Client();
		//Client(const char* ipAdress, int port);
		~Client();
		Client(const Client &other);
		Client &operator=(const Client &other);

		void setRequete(std::string requete);
		std::string getRequete() const;

		void setReponse(std::string reponse);
		std::string getReponse() const;

		int getSocketClient() const;
};

#endif
