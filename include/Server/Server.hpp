#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ConfigParser/ServerConfig.hpp"
#include "../Response/Response.hpp"
#include "../define.hpp"

//#define BUFFER_SIZE 50000
class Server
{
	private:
		int         			_port;
		std::string 			_ipAdress;
		int						_idx;
		int         			_opt;
		int        	 			_serverSocket;
		int         			_newSocket;
		int 	   				_socketCount;
		std::string        		_buffer;
		std::string 			_file;
		ssize_t      			_reading;
		ServerConfig			_serverConfig;
		struct sockaddr_in 		_addr;
		int						_statusCode;

	protected:

		virtual void onClientConnected(int clientSocket);
		virtual void onClientDisconnected(int clientSocket);

	public:
		// constructeur et destructeur
		Server();
		Server(std::string ipAdress, int port, ServerConfig conf, int idx);
		virtual ~Server();

		// constructeur par copie et operateur d'affectation
		Server(const Server &other);
		Server &operator=(const Server &other);

		// SETTERS
		void setFile(std::string file);
		void setResponse(std::string response);
		void setServerSocket(int serverSocket);
		void setReading(int reading);
		void setStatusCode(int statusCode);

		// GETTERS
		int				getServerSocket() const;
		int				getPort() const;
		int				getReading() const;
		std::string		getFile() const;
		std::string		getIpAdress() const;
		std::string		getBuffer() const;
		ServerConfig&	getServerConfigRef() const;
		ServerConfig	getServerConfig() const;
		int 			getIdx() const;
		int				getStatusCode() const;

		// Méthodes
		int Init();
		void sendToClient(int clientSocket, const char* message, int messageSize); // send message to client

};

#endif
