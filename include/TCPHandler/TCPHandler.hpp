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

		fd_set getMasterFdRead() const;
		void setMasterFdRead(fd_set masterFdRead);

		fd_set getMasterFdWrite() const;
		void setMasterFdWrite(fd_set masterFdWrite);

		std::vector<Server> getTabServers();
		void setTabServers(int size);

		//int getIdServer() const;



	private :
		std::vector<Server> _servers;
		std::vector<Client> _clients;

		fd_set _masterFdRead;
		fd_set _masterFdWrite;
		int _maxFd;
};

#endif
