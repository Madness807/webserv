#include "../include/TCPHandler/TCPHandler.hpp"

TCPHandler::TCPHandler()
{
		FD_ZERO(&_masterFdRead);
		FD_ZERO(&_masterFdWrite);
		_maxFd = 0;
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

void TCPHandler::setTabServers(int size) {
	std::vector<Server> servers(size);
	// for (int i = 0; i < size; i++)
	// {
    // 	servers.push_back(Server(ipAdress, port));
	// }
	servers.push_back(Server("127.0.0.1", 8080));
	servers.push_back(Server("127.0.0.1", 8888));
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
    // for (int i = 0; i < nbOfServer; i++)
    // {
	// 	//this->getTabServers()[i].setIpAdress(serverconfig.getIp(), serverconfig.getPort())
    //     this->getTabServers()[i].setIpAdress("127.0.0.1");
	// 	this->getTabServers()[i].setPort(8080);
	// 	this->getTabServers()[i].setIpAdress("127.0.0.1");
	// 	this->getTabServers()[i].setPort(8888);
    // }
	    // this->getTabServers()[0].setIpAdress("127.0.0.1");
		// this->getTabServers()[1].setPort(8080);
		// this->getTabServers()[0].setIpAdress("127.0.0.1");
		// this->getTabServers()[1].setPort(8888);
	// socket creation
	// -> int sockfd = socket(domain, type, protocol)
	// this->setServerSocket(socket(AF_INET, SOCK_STREAM, 0)); //= socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	// if (_serverSocket == -1)
	// {
	// 	std::cerr << "Error: server socket creation failed" << std::endl;
	// 	exit(EXIT_FAILURE);
	// }

	// // option to prevent error "address already in use”."
	// // -> int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen); // permet de reutiliser le port
	// if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt)) < 0) {
	// 	perror("setsockopt");
	// 	std::cerr << "Error: server setsockopt failed" << std::endl;
	// 	exit(EXIT_FAILURE);
	// }

	// // bind the socket to an address
	// //int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// if (bind(_serverSocket, (sockaddr *)&_addr, sizeof(_addr)) < 0)
	// {
	// 	perror("bind");
	// 	std::cerr << "Error: bind failed" << std::endl;
	// 	exit(EXIT_FAILURE);
	// }

	// if(listen(_serverSocket, 1) < 0)// mettre variable pour waiting list
	// {
	// 	std::cerr << "Error: listen failed" << std::endl;
	// 	exit(EXIT_FAILURE);
	// }

	// FD_ZERO(&_masterFdRead);
	// FD_ZERO(&_masterFdWrite);
	// FD_SET(_serverSocket, &_masterFdRead); // ajoute un fd a un ensemble de fd, en lien avec select, ajoute _serverSocket a _masterFd

	// return (0);
}

void TCPHandler::runServer() {
	// bool running = true;
	// int max_sd = _serverSocket;
	// std::vector<Client> clients(100);

	// std::cout << "Server is running" << std::endl;
	// while (running)
	// {
	// 	std::cout << "ip : " << _ipAdress << " port : " << _port << std::endl;
	// 	fd_set copy = _masterFdRead;
	// 	// See who's talking to us
	// 	_socketCount = select(max_sd + 1, &copy, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente

	// 	// Loop through all the current connections / potential connect
	// 	for (int i = 0; i <= max_sd; i++) //(int i = 0; _socketCount > 0; i++)
	// 	{
	// 		if (FD_ISSET(i, &copy) && i == _serverSocket)
	// 		{

	// 			clients[i].fillInfo(_serverSocket);

	// 			if(clients[i].getSocketClient() == -1) //if (clientSocket == -1)
	// 			{
	// 				std::cerr << "Error in accepting client";
	// 			}
	// 			if(clients[i].getSocketClient() > max_sd)//if (clientSocket > max_sd)
	// 			{
    //     			max_sd = clients[i].getSocketClient();
    // 			}
	// 			//std::cout << "socket client: " << clients[i].getSocketClient() << std::endl;
	// 			FD_SET(clients[i].getSocketClient(), &_masterFdRead);
	// 			// if (clients[i].getSocketClient() > 0)
	// 			// {
	// 			// 	onClientConnected(clients[i].getSocketClient());
	// 			// 	close(i);

	// 			// }
	// 			break;
	// 		}
	// 		if (FD_ISSET(i, &copy) && i != _serverSocket)
	// 		{
	// 			memset(_buffer, 0, sizeof(_buffer));
	// 			_reading = recv(i, _buffer, sizeof(_buffer), 0);
	// 			//std::cout << "Received: " << _buffer << std::endl;
	// 			// if (_buffer == "/quit")
	// 			// {
	// 			// 	running = false;
	// 			 	//onClientDisconnected(i);
	// 			// 	break;
	// 			// }
	// 			if (_reading <= 0)
	// 			{
	// 				close(i);
	// 				FD_CLR(i, &_masterFdRead);
	// 				//onClientDisconnected(i);
	// 			}
	// 			else
	// 			{
	// 				std::ifstream file(getFile().c_str());
	// 				//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/MITSUBISHI-Galant-2.5-V6-24V-Edition-Kombi-215000km-Benziner-Automat-2498ccm-161PS-6Zylinder-1580kg-104L-930x620.jpg");
	// 				//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/sitetest.html");

	// 				std::stringstream buffer;
	// 				buffer << file.rdbuf();

	// 				//std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg
	// 				//std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
	// 				std::string response = getResponse() + buffer.str();
	// 				send(i, response.c_str(), response.size(), 0);

	// 				close(i);

	// 			}
	// 			// else
	// 			// {

	// 			// 	clients[i].setBuffer(_buffer);
	// 			// 	this->sendToClient(i, _buffer, _reading);
	// 			// 	std::cout << "getBuffer: " << clients[i].getBuffer() << "Ii : " << i << std::endl;
	// 			// }
	// 			break;
	// 		}
	// 	}
	// }

	// while (FD_ISSET(_serverSocket, &_masterFdRead))
	// {
	// 	FD_CLR(_serverSocket, &_masterFdRead);
	// }
	// close(_serverSocket);
	// return 0;
}
