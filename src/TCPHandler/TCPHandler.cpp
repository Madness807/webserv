#include "../include/TCPHandler/TCPHandler.hpp"

TCPHandler::TCPHandler()
{
		FD_ZERO(&_masterFd);
		_maxFd = 0;
		_nbOfServer = 2;
}

TCPHandler::~TCPHandler() {}

TCPHandler::TCPHandler(const TCPHandler &other) {
	*this = other;
}

TCPHandler &TCPHandler::operator=(const TCPHandler &other) {
	if (this != &other) {
	}
	return *this;
}

int TCPHandler::getMaxFd() const {
	return _maxFd;
}

void TCPHandler::setMaxFd(int maxFd) {
	this->_maxFd = maxFd;
}

fd_set TCPHandler::getMasterFd() const {
	return this->_masterFd;
}

void TCPHandler::setMasterFd(fd_set masterFd) {
	this->_masterFd = masterFd;
}

std::vector<int> TCPHandler::getFdServers() const {
	return this->_fdServers;
}

std::vector<int> TCPHandler::getFdClients() const {
	return this->_fdClients;
}
// fd_set TCPHandler::getMasterFdWrite() const {
// 	return this->_masterFdWrite;
// }

// void TCPHandler::setMasterFdWrite(fd_set masterFdWrite) {
// 	this->_masterFdWrite = masterFdWrite;
// }

void TCPHandler::setTabServers(int size) { //utiliser une liste chaine et la parcourir pour init ip/port pour chaque server
	(void)size;
	std::vector<Server> servers(0);
	// for (int i = 0; i < size; i++)
	// {
    // 	servers.push_back(Server(ipAdress, port));
	// }
	servers.push_back(Server("127.0.0.1", 8080));
	servers.push_back(Server("127.0.0.1", 8888));

	std::cout << "ip server : " << servers[0].getIpAdress() << "port server " << servers[0].getPort() << std::endl;
	std::cout << "ip server : " << servers[1].getIpAdress() << "port server " << servers[1].getPort() << std::endl;

	this->_servers = servers;
}

std::vector<Server> TCPHandler::getTabServers() const {
	return this->_servers;
}

// int TCPHandler::getIdServer() const {
// 	return this->_idServer;
// }

void TCPHandler::initServer(int nbOfServer) {
	(void)nbOfServer;

	int serverSocket = 0;

	for (int i = 0; i < nbOfServer; i++)
	{

		_servers[i].setServerSocket(getTabServers()[i].Init()); // init server
		//_servers[i].setServerId(i);
		serverSocket = _servers[i].getServerSocket();
		if (serverSocket < 0)
			exit(EXIT_FAILURE);
		_fdServers.push_back(serverSocket);
		if (serverSocket > _maxFd)
			_maxFd = serverSocket;
		getTabServers()[i].setServerSocket(serverSocket);
		//std::cout << "maxFd " << _maxFd << " serversocket: " << serverSocket << std::endl;
	}
}


void TCPHandler::runServer()
{
	bool running = true;
	int socketCount = 0;
	std::vector<Client> clients(100);

	while (running)
	{
		FD_ZERO(&_masterFd);

		std::vector<int>fdServers = getFdServers();
		for (std::vector<int>::iterator it = fdServers.begin(); it != fdServers.end(); ++it)
		{
			FD_SET(*it, &_masterFd);
		}
		//std::cout << "check 1 " << std::endl;
		std::vector<int>fdClients = getFdClients();
		for (std::vector<int>::iterator it = fdClients.begin(); it != fdClients.end(); ++it)
		{
			FD_SET(*it, &_masterFd);
		}
		//std::cout << "check 2 " << std::endl;

		for (int i = 0; i < FD_SETSIZE; i++) {
		if (FD_ISSET(i, &_masterFd)) {
			std::cout << "File descriptor " << i << " is in the set" << std::endl;
		}
		}

		fd_set copy = _masterFd;
		socketCount = select(_maxFd + 1, &copy, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente
		std::cout << "socketCount: " << socketCount << std::endl;
		for (int i = 0; i <= _maxFd; i++)
		{
			if (FD_ISSET(i, &copy))
			{
				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
				{
					std::cout << ">> ip server : " << it->getIpAdress() << " port server : " << it->getPort() << " socketServer : " << it->getServerSocket() << std::endl;
					if (i == it->getServerSocket())
					{
						std::cout << "i == serverSocket" << std::endl;
						clients[i].fillInfo(it->getServerSocket());
						// while(clients[i].getSocketClient())
						// {
						_fdClients.push_back(clients[i].getSocketClient());
						// }
						std::vector<int> fdClients = getFdClients();
						for (std::vector<int>::iterator it = fdClients.begin(); it != fdClients.end(); ++it)
						{
						    std::cout << ">> ClientsSocket : " << *it << std::endl;
						}

						if(clients[i].getSocketClient() == -1) //if (clientSocket == -1)
						{
							perror("accept");
							std::cerr << "Error in accepting client";
						}
						if(clients[i].getSocketClient() > _maxFd)//if (clientSocket > max_sd)
						{
							_maxFd = clients[i].getSocketClient();
						}
						FD_SET(clients[i].getSocketClient(), &_masterFd);
					//	std::cout << "socket client: " << clients[i].getSocketClient() << " socketServer associated with : " << clients[i].getServerSocketAssociated() << std::endl;
					break;
					}
				}
			}
			if (FD_ISSET(i, &copy))
			{
				int reading = 0;
				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
				{
					if (i != it->getServerSocket())
					{
						//std::cout << ">> client socket : " << clients[i].getSocketClient() << std::endl;
						char tmp[BUFFER_SIZE];
						memset(tmp, 0, sizeof(tmp));
						reading = recv(clients[i].getSocketClient(), tmp, sizeof(tmp), 0);
						std::cout << "fdclient : " << *_fdClients.begin() << std::endl;
						//reading = recv(*_fdClients.begin(), tmp, sizeof(tmp), 0);

						it->setReading(reading);

						//std::cout << "reading: " << it->getReading() << std::endl;
						//std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;


						if (it->getReading() <= 0)
						{
							perror("recv");
							close(i);
							//FD_CLR(i, &_masterFdRead);
							//onClientDisconnected(i);
						}
						else
						{
							clients[i].setBuffer(tmp);
							it->sendToClient(clients[i].getSocketClient(), clients[i].getBuffer().c_str(), it->getReading());
							//it->sendToClient(clients[i].getSocketClient(), it->getBuffer().c_str(), it->getReading());

							//it->sendToClient(clients[i].getSocketClient(),"blabla", 7);
							//it->sendToClient(i, it->getBuffer().c_str(), it->getReading());
							std::cout << "getBuffer: " << clients[i].getBuffer() << "Ii : " << i << std::endl;
							std::cout << "socket client: " << clients[i].getSocketClient() << " socketServer associated with : " << clients[i].getServerSocketAssociated() << std::endl;
							close(_fdClients[i]);
							//_fdClients.erase(_fdClients.begin() + i); // a adapter
						}
						break;
					}
				}
			}
		}
	}

	//int i = 0;
	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		// FD_CLR(it->getServerSocket(), &_masterFdRead);
		close(it->getServerSocket());
	}

	// while (FD_ISSET(_servers[i].getServerSocket(), &_masterFdRead))
	// {
	// 	FD_CLR(_servers[i].getServerSocket(), &_masterFdRead);
	// }
	// close(_servers[i].getServerSocket());
}




// void TCPHandler::runServer()
// {
// 	bool running = true;
// 	int socketCount = 0;
// 	//int reading = 0;
// 	std::vector<Client> clients(100);

// 	while (running)
// 	{
// 		//std::cout << "ip : " << _ipAdress << " port : " << _port << std::endl;
// 		fd_set copyRead = _masterFdRead;
// 		//fd_set copyWrite = _masterFdWrite;
// 		// See who's talking to us
// 		socketCount = select(_maxFd + 1, &copyRead, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente
// 		//std::cout << "socketCount: " << socketCount << std::endl;
// 		// Loop through all the current connections / potential connect
// 		for (int i = 0; i <= _maxFd; i++)
// 		{
// 		//	std::cout << "i : " << i << std::endl;
// 		//	std::cout << "server PORT : " << _servers[0].getPort() << std::endl;
// 		//	std::cout << "server SOCKET : " << _servers[0].getServerSocket() << std::endl;

// 			if (FD_ISSET(i, &copyRead))
// 			{
// 				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
// 				{

// 					std::cout << ">> ip server : " << it->getIpAdress() << " port server : " << it->getPort() << " socketServer : " << it->getServerSocket() << std::endl;

// 					if (i == it->getServerSocket())
// 					{
// 						std::cout << "i == serverSocket" << std::endl;
// 						clients[i].fillInfo(it->getServerSocket());

// 						if(clients[i].getSocketClient() == -1) //if (clientSocket == -1)
// 						{
// 							perror("accept");
// 							std::cerr << "Error in accepting client";
// 						}
// 						if(clients[i].getSocketClient() > _maxFd)//if (clientSocket > max_sd)
// 						{
// 							_maxFd = clients[i].getSocketClient();
// 						}
// 						FD_SET(clients[i].getSocketClient(), &_masterFdRead);
// 					//	std::cout << "socket client: " << clients[i].getSocketClient() << " socketServer associated with : " << clients[i].getServerSocketAssociated() << std::endl;
// 					break;
// 					}
// 				}
// 			}
// 			if (FD_ISSET(i, &copyRead))
// 			{
// 				int reading = 0;
// 				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
// 				{
// 					if (i != it->getServerSocket())
// 					{
// 						// it->getBuffer().assign(BUFFER_SIZE, 0);
// 						//std::cout << ">>>> ip server : " << it->getIpAdress() << " port server : " << it->getPort() << " socketServer : " << it->getServerSocket() << " client i : " << i << std::endl;
// 						//std::cout << ">> client socket : " << clients[i].getSocketClient() << std::endl;
// 						char tmp[BUFFER_SIZE];
// 						memset(tmp, 0, sizeof(tmp));
// 						reading = recv(clients[i].getSocketClient(), tmp, sizeof(tmp), 0);

// 						it->setReading(reading);

// 						//std::cout << "reading: " << it->getReading() << std::endl;
// 						std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;


// 						if (it->getReading() <= 0)
// 						{
// 							perror("recv");
// 							close(i);
// 							FD_CLR(i, &_masterFdRead);
// 							//onClientDisconnected(i);
// 						}
// 						else
// 						{
// 							std::cout << ">> getBuffer: " << it->getBuffer() << std::endl;
// 							clients[i].setBuffer(tmp);
// 							it->sendToClient(clients[i].getSocketClient(), clients[i].getBuffer().c_str(), it->getReading());
// 							//it->sendToClient(clients[i].getSocketClient(), it->getBuffer().c_str(), it->getReading());

// 							//it->sendToClient(clients[i].getSocketClient(),"blabla", 7);
// 							//it->sendToClient(i, it->getBuffer().c_str(), it->getReading());
// 							std::cout << "getBuffer: " << clients[i].getBuffer() << "Ii : " << i << std::endl;
// 							std::cout << "socket client: " << clients[i].getSocketClient() << " socketServer associated with : " << clients[i].getServerSocketAssociated() << std::endl;

// 						}
// 						break;
// 					}
// 				}
// 			}
// 		}
// 	}

// 	//int i = 0;
// 	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
// 	{
// 		FD_CLR(it->getServerSocket(), &_masterFdRead);
// 		close(it->getServerSocket());
// 	}

// 	// while (FD_ISSET(_servers[i].getServerSocket(), &_masterFdRead))
// 	// {
// 	// 	FD_CLR(_servers[i].getServerSocket(), &_masterFdRead);
// 	// }
// 	// close(_servers[i].getServerSocket());
// }

