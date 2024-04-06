#include "../include/TCPHandler/TCPHandler.hpp"

TCPHandler::TCPHandler()
{
		FD_ZERO(&_masterFdRead);
		FD_ZERO(&_masterFdWrite);
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

fd_set TCPHandler::getMasterFdRead() const {
	return this->_masterFdRead;
}

void TCPHandler::setMasterFdRead(fd_set masterFdRead) {
	this->_masterFdRead = masterFdRead;
}

fd_set TCPHandler::getMasterFdWrite() const {
	return this->_masterFdWrite;
}

void TCPHandler::setMasterFdWrite(fd_set masterFdWrite) {
	this->_masterFdWrite = masterFdWrite;
}

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

std::vector<Server> TCPHandler::getTabServers() {
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
		FD_SET(serverSocket, &_masterFdRead);
		if (serverSocket > _maxFd)
			_maxFd = serverSocket;
		getTabServers()[i].setServerSocket(serverSocket);
		//std::cout << "maxFd " << _maxFd << " serversocket: " << serverSocket << std::endl;
		//std::cout << "serverSocket: " << _servers[i].getServerSocket() << " serverId : " << _servers[i].getServerId() << std::endl;
		//this->getTabServers()[i].Run();
	}

}


void TCPHandler::runServer()
{
	bool running = true;
	int socketCount = 0;
	//int reading = 0;
	std::vector<Client> clients(100);

	while (running)
	{
		//std::cout << "ip : " << _ipAdress << " port : " << _port << std::endl;
		fd_set copyRead = _masterFdRead;
		//fd_set copyWrite = _masterFdWrite;
		// See who's talking to us
		socketCount = select(_maxFd + 1, &copyRead, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente
		//std::cout << "socketCount: " << socketCount << std::endl;
		// Loop through all the current connections / potential connect
		for (int i = 0; i <= _maxFd; i++)
		{
		//	std::cout << "i : " << i << std::endl;
		//	std::cout << "server PORT : " << _servers[0].getPort() << std::endl;
		//	std::cout << "server SOCKET : " << _servers[0].getServerSocket() << std::endl;

			if (FD_ISSET(i, &copyRead))
			{
				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
				{

					std::cout << ">> ip server : " << it->getIpAdress() << " port server : " << it->getPort() << " socketServer : " << it->getServerSocket() << std::endl;

					if (i == it->getServerSocket())
					{
						std::cout << "i == serverSocket" << std::endl;
						clients[i].fillInfo(it->getServerSocket());

						if(clients[i].getSocketClient() == -1) //if (clientSocket == -1)
						{
							perror("accept");
							std::cerr << "Error in accepting client";
						}
						if(clients[i].getSocketClient() > _maxFd)//if (clientSocket > max_sd)
						{
							_maxFd = clients[i].getSocketClient();
						}
						FD_SET(clients[i].getSocketClient(), &_masterFdRead);
					//	std::cout << "socket client: " << clients[i].getSocketClient() << " socketServer associated with : " << clients[i].getServerSocketAssociated() << std::endl;
					break;
					}
				}
			}
			if (FD_ISSET(i, &copyRead))
			{
				int reading = 0;
				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
				{
					if (i != it->getServerSocket())
					{
						// it->getBuffer().assign(BUFFER_SIZE, 0);
						//std::cout << ">>>> ip server : " << it->getIpAdress() << " port server : " << it->getPort() << " socketServer : " << it->getServerSocket() << " client i : " << i << std::endl;
						//std::cout << ">> client socket : " << clients[i].getSocketClient() << std::endl;
						char tmp[BUFFER_SIZE];
						memset(tmp, 0, sizeof(tmp));
						reading = recv(clients[i].getSocketClient(), tmp, sizeof(tmp), 0);

						it->setReading(reading);

						//std::cout << "reading: " << it->getReading() << std::endl;
						std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;


						if (it->getReading() <= 0)
						{
							perror("recv");
							close(i);
							FD_CLR(i, &_masterFdRead);
							//onClientDisconnected(i);
						}
						else
						{
							std::cout << ">> getBuffer: " << it->getBuffer() << std::endl;
							clients[i].setBuffer(tmp);
							it->sendToClient(clients[i].getSocketClient(), clients[i].getBuffer().c_str(), it->getReading());
							//it->sendToClient(clients[i].getSocketClient(), it->getBuffer().c_str(), it->getReading());

							//it->sendToClient(clients[i].getSocketClient(),"blabla", 7);
							//it->sendToClient(i, it->getBuffer().c_str(), it->getReading());
							std::cout << "getBuffer: " << clients[i].getBuffer() << "Ii : " << i << std::endl;
							std::cout << "socket client: " << clients[i].getSocketClient() << " socketServer associated with : " << clients[i].getServerSocketAssociated() << std::endl;

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
		FD_CLR(it->getServerSocket(), &_masterFdRead);
		close(it->getServerSocket());
	}

	// while (FD_ISSET(_servers[i].getServerSocket(), &_masterFdRead))
	// {
	// 	FD_CLR(_servers[i].getServerSocket(), &_masterFdRead);
	// }
	// close(_servers[i].getServerSocket());
}

// void TCPHandler::runServer() {
// 	bool running = true;
// 	int socketCount = 0;
// 	int reading = 0;
// 	std::vector<Client> clients(100);

// 	std::cout << "Main Server is running" << std::endl;
// 	while (running)
// 	{
// 		//std::cout << "ip : " << _ipAdress << " port : " << _port << std::endl;
// 		fd_set copy = _masterFdRead;
// 		// See who's talking to us
// 		socketCount = select(_maxFd + 1, &copy, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente
// 		std::cout << "socketCount: " << socketCount << std::endl;
// 		std::cout <<"serverSocket: " << _servers[0].getServerSocket() << std::endl;
// 		// Loop through all the current connections / potential connect
// 		for (int i = 0; i <= _maxFd; i++)
// 		{
// 		//	std::cout << "i : " << i << std::endl;
// 		//	std::cout << "server PORT : " << _servers[0].getPort() << std::endl;
// 		//	std::cout << "server SOCKET : " << _servers[0].getServerSocket() << std::endl;

// 			if (FD_ISSET(i, &copy) && i == _servers[0].getServerSocket())
// 			{
// 				std::cout << "i == serverSocket" << std::endl;

// 				clients[i].fillInfo(_servers[0].getServerSocket());

// 				if(clients[i].getSocketClient() == -1) //if (clientSocket == -1)
// 				{
// 					std::cerr << "Error in accepting client";
// 				}
// 				if(clients[i].getSocketClient() > _maxFd)//if (clientSocket > max_sd)
// 				{
//         			_maxFd = clients[i].getSocketClient();
//     			}
// 				//std::cout << "socket client: " << clients[i].getSocketClient() << std::endl;
// 				// if (clients[i].getSocketClient() > 0)
// 				// {
// 				// 	onClientConnected(clients[i].getSocketClient());
// 				// 	close(i);

// 				// }
// 				break;
// 			}
// 			if (FD_ISSET(i, &copy) && i != _servers[0].getServerSocket())
// 			{
// 				_servers[0].getBuffer().assign(BUFFER_SIZE, 0);
// 				//_buffer.assign(BUFFER_SIZE, 0);
// 				//memset(_buffer, 0, sizeof(_buffer));
// 				//reading = recv(i, buffer, sizeof(buffer), 0);
// 				reading = recv(_servers[0].getServerSocket(), &(_servers[0].getBuffer())[0], sizeof(_servers[0].getBuffer()), 0);
// 				std::cout << "reading: " << reading << std::endl;
// 				//std::cout << "Received: " << _buffer << std::endl;
// 				// if (_buffer == "/quit")
// 				// {
// 				// 	running = false;
// 				 	//onClientDisconnected(i);
// 				// 	break;
// 				// }
// 				if (reading <= 0)
// 				{
// 					perror("recv");
// 					close(i);
// 					FD_CLR(i, &_masterFdRead);
// 					//onClientDisconnected(i);
// 				}
// 				// else
// 				// {
// 				// 	//std::ifstream file(_servers[i].getFile().c_str());
// 				// 	//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/MITSUBISHI-Galant-2.5-V6-24V-Edition-Kombi-215000km-Benziner-Automat-2498ccm-161PS-6Zylinder-1580kg-104L-930x620.jpg");
// 				// 	std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/sitetest.html");

// 				// 	std::stringstream buffer;
// 				// 	buffer << file.rdbuf();

// 				// 	std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg
// 				// 	//std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
// 				// 	//std::string response = _servers[i].getResponse() + buffer.str();
// 				// 	send(i, response.c_str(), response.size(), 0);

// 				// 	close(i);

// 				// }
// 				else
// 				{

// 					clients[i].setBuffer(_servers[0].getBuffer());
// 					//this->sendToClient(i, _servers[i].getBuffer(), reading);
// 					_servers[0].sendToClient(i, _servers[0].getBuffer().c_str(), reading);
// 					std::cout << "getBuffer: " << clients[i].getBuffer() << "Ii : " << i << std::endl;
// 				}
// 				break;
// 			}
// 		}
// 	}
// 	int i = 0;
// 	while (FD_ISSET(_servers[i].getServerSocket(), &_masterFdRead))
// 	{
// 		FD_CLR(_servers[i].getServerSocket(), &_masterFdRead);
// 	}
// 	close(_servers[i].getServerSocket());
// 	//return 0;
// }
