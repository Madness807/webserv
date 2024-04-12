#include "../include/TCPHandler/TCPHandler.hpp"
#include <fcntl.h>
TCPHandler* g_tcpHandlerInstance = NULL;
void globalSignalHandler(int signal);

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


void TCPHandler::setTabServers(int size) { //utiliser une liste chaine et la parcourir pour init ip/port pour chaque server
	(void)size;
	std::vector<Server> servers;
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

void TCPHandler::initServer(int nbOfServer) {
	(void)nbOfServer;

	int serverSocket = 0;

	for (int i = 0; i < nbOfServer; i++)
	{
		_servers[i].setServerSocket(getTabServers()[i].Init()); // init server
		serverSocket = _servers[i].getServerSocket();
		if (serverSocket < 0)
			exit(0);
		_fdServers.push_back(serverSocket);
		if (serverSocket > _maxFd)
			_maxFd = serverSocket;
		getTabServers()[i].setServerSocket(serverSocket);
		//std::cout << "maxFd " << _maxFd << " serversocket: " << serverSocket << std::endl;
	}
}

int TCPHandler::closeFd() {

	std::cout << "Signal SIGINT received" << std::endl;

	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		std::cout << "CLOSING -> it->getServerSocket() : " << it->getServerSocket() << std::endl;
		close(it->getServerSocket());
	}
	std::vector<int>fdClients = getFdClients();
	for (size_t i = 0; i < fdClients.size(); i++)
	{
		std::cout << "CLOSING -> fdClients[i] : " << fdClients[i] << std::endl;
		close(fdClients[i]);
	}
	exit(0);
}

void globalSignalHandler(int signal) {
	if (signal == SIGINT)
	{
		if(g_tcpHandlerInstance != NULL)
			g_tcpHandlerInstance->closeFd();
	}
	exit(0);
}

void TCPHandler::runServer()
{
	bool running = true;
	int socketCount = 0;
	//std::map<int, Client> clients;

	g_tcpHandlerInstance = this;
	signal(SIGINT, globalSignalHandler);

	while (running)
	{
		setupMasterFd();
		for (int i = 0; i < FD_SETSIZE; i++) {
		if (FD_ISSET(i, &_masterFd)) {
			std::cout << "File descriptor " << i << " is in the set" << std::endl;
		}
		}

		fd_set *copy = &_masterFd;
		socketCount = select(_maxFd + 1, copy, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente
		std::cout << "socketCount: " << std::strerror(errno) << socketCount << std::endl;
		for (int i = 0; i <= _maxFd; i++)
		{
			if (FD_ISSET(i, copy))
			{
				handlingNewClient(i);
			}
			if (FD_ISSET(i, copy))
			{
<<<<<<< HEAD
				handlingNewRequest(i);
=======
				int reading = 0;
				for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
				{
					if (_clients.count(i) > 0) // verif si cle i existe
					{
						Client& client = _clients[i]; // recup valeur se trouvnt a la cle i
						if (i != it->getServerSocket())
						{
							//std::cout << ">> client socket : " << client.getSocketClient() << std::endl;
							char tmp[BUFFER_SIZE];
							memset(tmp, 0, sizeof(tmp));
							reading = recv(client.getSocketClient(), tmp, sizeof(tmp), 0);

							//std::cout << "fdclient *_fdClients.begin() : " << *_fdClients.begin() << std::endl;
							std::cout << "fdclient newClient.getSocketClient() : " << client.getSocketClient() << std::endl;
							it->setReading(reading);

							//std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;
							if (it->getReading() <= 0)
							{
								perror("recv");
								close(client.getSocketClient());
								for (std::vector<int>::iterator it = _fdClients.begin(); it != _fdClients.end();)
								{
									if (*it == client.getSocketClient())
									{
										std::cout << "ClientsSocket to erase: " << *it << std::endl;
										it = _fdClients.erase(it); // erase renvoie un itérateur vers l'élément suivant
									}
									else
										++it;
								}
							}
							else
							{
								// std::ifstream file(getFile().c_str());
								std::ifstream file("/home/jo/42/webserv/website/MITSUBISHI-Galant-2.5-V6-24V-Edition-Kombi-215000km-Benziner-Automat-2498ccm-161PS-6Zylinder-1580kg-104L-930x620.jpg");
								//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/sitetest.html");

								std::stringstream buffer;
								buffer << file.rdbuf();

								std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
								//std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg
								//std::string response = getResponse() + buffer.str();
								send(client.getSocketClient(), response.c_str(), response.size(), 0);
								std::cout << "Closing fd client" << std::endl;
								close(client.getSocketClient());

								client.setSocketClient(-1);

							}
							// else
							// {
							// 	client.setBuffer(tmp);
							// 	it->sendToClient(client.getSocketClient(), client.getBuffer().c_str(), it->getReading());
							// 	//it->sendToClient(client.getSocketClient(), client.getBuffer().c_str(), it->getReading());
							// 	std::cout << "getBuffer: " << client.getBuffer() << "I : " << i << std::endl;
							// 	std::cout << "socket client: " << client.getSocketClient() << " socketServer associated with : " << client.getServerSocketAssociated() << std::endl;
							// }
							break;
						}
					}
				}
>>>>>>> origin/main
			}
		}
	}

}


int TCPHandler::setupMasterFd()
{
		FD_ZERO(&_masterFd);

		std::vector<int>fdServers = getFdServers();
		for (std::vector<int>::iterator it = fdServers.begin(); it != fdServers.end(); ++it)
		{
			FD_SET(*it, &_masterFd);
		}

		std::vector<int>fdClients = getFdClients();
		for (std::vector<int>::iterator it = fdClients.begin(); it != fdClients.end(); ++it)
		{
			std::cout << "+++++ fdClients : " << *it << std::endl;
			if(fcntl(*it, F_GETFL, 0) == -1)
			{
				perror("fcntl");
				std::cerr << "Invalid fd : " << *it << std::endl;
			}
			else
				FD_SET(*it, &_masterFd);
		}
		return (0);
}


int TCPHandler::handlingNewClient(int i)
{
	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{

		std::cout << "i : " << i << " serverSocket : " << it->getServerSocket() << std::endl;
		if (i == it->getServerSocket())
		{
			std::cout << "i == serverSocket" << std::endl;
			Client newClient;
			newClient.fillInfo(it->getServerSocket());
			_clients[newClient.getSocketClient()] = newClient;
			std::cout << "-------- newClient.getSocketClient() : " << newClient.getSocketClient() << " sockerServer : " << newClient.getServerSocketAssociated() << std::endl;
			_fdClients.push_back(newClient.getSocketClient());

			// std::vector<int> fdClients = getFdClients();
			// for (std::vector<int>::iterator it = fdClients.begin(); it != fdClients.end(); ++it)
			// {
			// 	std::cout << ">> ClientsSocket : " << *it << std::endl;
			// }

			if(newClient.getSocketClient() == -1)
			{
				perror("accept");
				std::cerr << "Error in accepting client";
			}

			if(newClient.getSocketClient() > _maxFd)
			{
				_maxFd = newClient.getSocketClient();
			}
			break;
		}
	}
	return (0);
}

int TCPHandler::handlingNewRequest(int i)
{
	int reading = 0;
	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		if (_clients.count(i) > 0) // verif si cle i existe
		{
			Client& client = _clients[i]; // recup valeur se trouvnt a la cle i
			if (i != it->getServerSocket())
			{
				//std::cout << ">> client socket : " << client.getSocketClient() << std::endl;
				char tmp[BUFFER_SIZE];
				memset(tmp, 0, sizeof(tmp));
				reading = recv(client.getSocketClient(), tmp, sizeof(tmp), 0);

				//std::cout << "fdclient *_fdClients.begin() : " << *_fdClients.begin() << std::endl;
				std::cout << "fdclient newClient.getSocketClient() : " << client.getSocketClient() << std::endl;
				it->setReading(reading);

				//std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;
				if (it->getReading() <= 0)
				{
					//clientIsDisconnected();
					perror("recv");
					close(client.getSocketClient());
					for (std::vector<int>::iterator it = _fdClients.begin(); it != _fdClients.end();)
					{
						if (*it == client.getSocketClient())
						{
							std::cout << "ClientsSocket to erase: " << *it << " Client is disconnected" << std::endl;
							it = _fdClients.erase(it); // erase renvoie un itérateur vers l'élément suivant
						}
						else
							++it;
					}
				}
				else
				{
					// std::ifstream file(getFile().c_str());
					//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/MITSUBISHI-Galant-2.5-V6-24V-Edition-Kombi-215000km-Benziner-Automat-2498ccm-161PS-6Zylinder-1580kg-104L-930x620.jpg");
					std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/sitetest.html");

					std::stringstream buffer;
					buffer << file.rdbuf();

					//std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
					std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg
					//std::string response = getResponse() + buffer.str();
					send(client.getSocketClient(), response.c_str(), response.size(), 0);
					std::cout << "Closing fd client" << std::endl;
					close(client.getSocketClient());

					client.setSocketClient(-1);

				}
				break;
			}
		}
	}
	return (0);
}

// int clientIsDisconnected(int clientSocket)
// {
// 	perror("recv");
// 	close(client.getSocketClient());
// 	for (std::vector<int>::iterator it = _fdClients.begin(); it != _fdClients.end();)
// 	{
// 		if (*it == client.getSocketClient())
// 		{
// 			std::cout << "ClientsSocket to erase: " << *it << " Client is disconnected" << std::endl;
// 			it = _fdClients.erase(it); // erase renvoie un itérateur vers l'élément suivant
// 		}
// 		else
// 			++it;
// 	}
// 	return (0);
// }
