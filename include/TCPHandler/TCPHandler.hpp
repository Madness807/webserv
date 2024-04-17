#ifndef TCP_HPP
#define TCP_HPP

#include "../Server/Server.hpp"
#include "../client/Client.hpp"
#include "../../include/Connection/Connection.hpp"
#include "../ConfigParser/ServerManager.hpp"
#include "../ConfigParser/ConfigParser.hpp"
#include "../Response/Response.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <cstring>


class TCPHandler
{
	private :
		std::vector<Server> _servers;
		std::map<int, Client> _clients;
		fd_set _masterFd;
		std::vector<int> _fdServers;
		std::vector<int> _fdClients;
		int _maxFd;
		int _nbOfServer;
		ServerManager _serverManager;

	public :
		// constructeur et destructeur
		TCPHandler();
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
		std::vector<int> getFdClients() const;
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
};

#endif
