#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Connection/Connection.hpp"
#include "../Response/Response.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024
class Client
{
	private:
		int					_socketClient;
		int					_serverSocketAssociated;
		std::string			_clientRequete;
		std::string			_clientReponse;
		std::string			_buffer; // pour upload image et pour pas bloquer sur \0 qui se promene
		struct sockaddr_in 	_addrClient;
		socklen_t			_addrClientSize;

	public:
		// constructeur et destructeur
		Client();
		//Client(const char* ipAdress, int port);
		~Client();

		// constructeur par copie et operateur d'affectation
		Client(const Client &other);
		Client &operator=(const Client &other);

		// SETTERS
		//void setRequete(std::string requete);
		//void setReponse(std::string reponse);
		void setSocketClient(int socketClient);
		void setBuffer(std::string message);
		void setAddrClient(struct sockaddr_in addrClient);
		void setAddrClientSize(socklen_t size);
		void setServerSocketAssociated(int serverSocket);
		//void setSocketClient(int socketClient, socklen_t addrSize);

		// GETTERS
		//std::string getRequete() const;
		//std::string getReponse() const;
		std::string getBuffer() const;
		socklen_t getAddrClientSize() const;
		int getSocketClient() const;
		int getServerSocketAssociated() const;
		const struct sockaddr_in& getAddrClient() const;

		// METHODES
		void fillInfo(int serverSocket);
};

#endif
