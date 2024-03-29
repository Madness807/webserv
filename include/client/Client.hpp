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
		int					_socketClient;
		std::string			_clientRequete;
		std::string			_clientReponse;
		std::string			_buffer[1024]; // pour upload image et pour pas bloquer sur \0 qui se promene
		struct sockaddr_in 	_addrClient;
		socklen_t			_addrClientSize;

	public:
		Client();
		//Client(const char* ipAdress, int port);
		~Client();
		Client(const Client &other);
		Client &operator=(const Client &other);

		std::string getRequete() const;
		void setRequete(std::string requete);

		std::string getReponse() const;
		void setReponse(std::string reponse);

		int getSocketClient() const;
		void setSocketClient(int socketClient, socklen_t addrSize) {
    		_socketClient = socketClient;
    		_addrClientSize = addrSize;
		}


		std::string getBuffer() const;
		void setBuffer(std::string message);


		socklen_t getAddrClientSize() const {
        	return sizeof(this->_addrClient);
    	}
		void setAddrClientSize(socklen_t size) {

			_addrClientSize = size;
		}

		const struct sockaddr_in& getAddrClient() const {
			return _addrClient;
		}

};

#endif
