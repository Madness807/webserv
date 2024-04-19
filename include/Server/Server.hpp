#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../include/ConfigParser/ConfigParser.hpp"
#include "../../include/Connection/Connection.hpp"
#include "../ConfigParser/ServerConfig.hpp"
#include "../define.hpp"

#define BUFFER_SIZE 1024
class Server
{
	private:
		int         			_opt;
		int        	 			_serverSocket;
		int         			_newSocket;
		int         			_port;
		int 	   				_socketCount;
		std::string 			_ipAdress;
		std::string        		_buffer;
		std::string 			_file;
		ssize_t      			_reading;
		struct sockaddr_in 		_addr;
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
		int				getServerSocket() const;
		int				getPort() const;
		int				getReading() const;
		std::string		getFile() const;
		std::string		getIpAdress() const;
		std::string		getBuffer() const;
		ServerConfig&	getServerConfigRef() const;

		// Méthodes
		int Init();
		void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client

};

#endif
