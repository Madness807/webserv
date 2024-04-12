#ifndef TCP_HPP
#define TCP_HPP

#include "../Server/Server.hpp"
#include "../client/Client.hpp"
#include "../../include/ConfigParser/ConfigParser.hpp"
#include "../../include/Connection/Connection.hpp"
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

		// fd_set getMasterFdWrite() const;
		// void setMasterFdWrite(fd_set masterFdWrite);

		std::vector<Server> getTabServers() const;
		void setTabServers(int size);
		int closeFd();
		void my_handler(int s);
		std::vector<int> getFdServers() const;
		std::vector<int> getFdClients() const;

		int setupMasterFd();
		int handlingNewClient(int i);
		int handlingNewRequest(int i);
		//int clientIsDisconnected(int i, );
		//void setFdServers(int size);

		//int getIdServer() const;



	private :
		std::vector<Server> _servers;
		std::map<int, Client> _clients;
		//std::vector<Client> _clients;

		fd_set _masterFd;
		std::vector<int> _fdServers;
		std::vector<int> _fdClients;

		int _maxFd;
		int _nbOfServer;
};

#endif
