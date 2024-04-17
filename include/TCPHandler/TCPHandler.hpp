#ifndef TCP_HPP
#define TCP_HPP

#include "../Server/Server.hpp"
#include "../client/Client.hpp"
#include "../../include/Connection/Connection.hpp"
#include "../ConfigParser/ServerManager.hpp"
#include "../ConfigParser/ConfigParser.hpp"
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
	public :
		TCPHandler();
		~TCPHandler();
		TCPHandler(const TCPHandler &other);
		TCPHandler &operator=(const TCPHandler &other);

		void initServer(int nbOfServer);
		void runServer();

		int getMaxFd() const;
		void setMaxFd(int maxFd);

		fd_set getMasterFd() const;
		void setMasterFd(fd_set masterFd);

		std::vector<Server> getTabServers() const;
		void setTabServers(int size);

		void setTabServers(ServerManager &server_manager);
		int closeFd();

		std::vector<int> getFdServers() const;
		std::vector<int> getFdClients() const;

		int getNbOfServer() const;

		int setupMasterFd();
		int handlingNewClient(int i);
		int handlingCommunication(int i);
		int createNewClient(int socketServer);
		int handlingRequest(Client &client);
		int handlingResponse(Client &client);
		int clientIsDisconnected(Client &client);

	private :
		std::vector<Server> _servers;
		std::map<int, Client> _clients;

		fd_set _masterFd;
		std::vector<int> _fdServers;
		std::vector<int> _fdClients;

		int _maxFd;
		int _nbOfServer;

		ServerManager _serverManager;
};

#endif
