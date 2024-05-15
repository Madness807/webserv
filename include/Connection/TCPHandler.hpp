#ifndef TCP_HPP
#define TCP_HPP

#include "../Server/Server.hpp"
#include "../client/Client.hpp"
#include "../ConfigParser/ServerManager.hpp"
#include "../ConfigParser/ConfigParser.hpp"
#include "../Response/Response.hpp"
#include "../define.hpp"
#include "../utils/utils.hpp"

#define BUFFER_SIZE 30000
class TCPHandler
{
	private :
		std::vector<Server> 	_servers;
		std::map<int, Client> 	_clients;
		fd_set 					_masterFd;
		std::vector<int> 		_fdServers;
		std::vector<int>&		_fdClients;
		int 					_maxFd;
		int 					_nbOfServer;
		ServerManager 			_serverManager;
		Response				_response;

	public :
		// constructeur et destructeur
		TCPHandler();
		TCPHandler(std::vector<int>& clients);
		~TCPHandler();

		// constructeur par copie et operateur d'affectation
		TCPHandler(const TCPHandler &other);
		TCPHandler &operator=(const TCPHandler &other);

		// SETTERS
		void setMaxFd(int maxFd);
		void setMasterFd(fd_set masterFd);
		void setTabServers(ServerManager &server_manager);
		void setServerManager(ServerManager &serverManager);

		// GETTERS
		int getMaxFd() const;
		fd_set getMasterFd() const;
		int getNbOfServer() const;
		std::vector<int> getFdServers() const;
		std::vector<int> &getFdClients() const;
		std::vector<Server> getTabServers() const;

		// Méthodes
		void initServer();
		void runServer();
		int closeFd();
		int setupMasterFd();
		int handlingNewClient(int i);
		int handlingCommunication(int i);
		int createNewClient(int socketServer);
		int handlingRequest(Client &client);
		int handlingResponse(Client &client);
		int clientIsDisconnected(Client &client);

		// DEBUG
		void printSocketState();
		void printNewClientStatus(bool clientConnected, int port);
		void printNewClientInfo(const Client& newClient);
};

void globalSignalHandler(int signal);

#endif
