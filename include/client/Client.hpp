#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Server/Server.hpp"
#include "../Response/Response.hpp"

//#define BUFFER_SIZE 30000
class Client
{
	private:
		int					_idxServer;
		int					_socketClient;
		int					_serverSocketAssociated;
		std::string			_clientRequete;
		std::string			_clientReponse;
		std::string			_buffer;
		struct sockaddr_in 	_addrClient;
		socklen_t			_addrClientSize;

	public:
		// constructeur et destructeur
		Client();
		~Client();

		// constructeur par copie et operateur d'affectation
		Client(const Client &other);
		Client &operator=(const Client &other);

		// SETTERS
		void						setSocketClient(int socketClient);
		void						setBuffer(std::string message);
		void						setAddrClient(struct sockaddr_in addrClient);
		void						setAddrClientSize(socklen_t size);
		void						setServerSocketAssociated(int serverSocket);

		// GETTERS
		std::string					getBuffer() const;
		socklen_t					getAddrClientSize() const;
		int							getSocketClient() const;
		int							getServerSocketAssociated() const;
		const struct sockaddr_in&	getAddrClient() const;
		int							getServerIdx()const;

		// METHODES
		int							fillInfo(int serverSocket, std::vector<Server> &server);
};

#endif
