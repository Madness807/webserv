#include "../../include/Connection/TCPHandler.hpp"

TCPHandler *g_tcpHandlerInstance = NULL;
void globalSignalHandler(int signal);

// ##################################################################
//                    Constructor && Destructor                     #
// ##################################################################

TCPHandler::TCPHandler(std::vector<int>& clients) :  _fdClients(clients), _response()
{
	FD_ZERO(&_masterFd);
	_maxFd = 0;
	_nbOfServer = 0;
}

TCPHandler::~TCPHandler() {}

// ##################################################################
//		constructeur par copie et operateur d'affectation		   #
// ##################################################################
TCPHandler::TCPHandler(const TCPHandler &other) : _fdClients(other._fdClients), _response(other._response)
{
	*this = other;
}

TCPHandler &TCPHandler::operator=(const TCPHandler &other)
{
	if (this != &other)
	{
		_servers = other._servers;
		_clients = other._clients;
		_masterFd = other._masterFd;
		_fdServers = other._fdServers;
		_fdClients = other._fdClients;
		_maxFd = other._maxFd;
		_nbOfServer = other._nbOfServer;
		_serverManager = other._serverManager;
		_response = other._response;
	}
	return *this;
}

// ##################################################################
//                           SETTERS                                #
// ##################################################################
void TCPHandler::setMaxFd(int maxFd)
{
	this->_maxFd = maxFd;
}

void TCPHandler::setMasterFd(fd_set masterFd)
{
	this->_masterFd = masterFd;
}

void TCPHandler::setServerManager(ServerManager &serverManager)
{
	this->_serverManager = serverManager;
}

void TCPHandler::setTabServers(ServerManager &server_manager)
{
	this->_serverManager = server_manager;
	std::vector<Server> servers;
	const std::vector<ServerConfig> serverConfigs = this->_serverManager.getServerConfig();
	int count = 0;

	for (std::vector<ServerConfig>::const_iterator it = serverConfigs.begin(); it != serverConfigs.end(); ++it)
	{
		Server newserver(it->getIp(), it->getPort(), *it, count);
		count++;
		servers.push_back(newserver);
	}

	this->_servers = servers;
}

// ##################################################################
//                           GETTERS                                #
// ##################################################################
int TCPHandler::getMaxFd() const
{
	return _maxFd;
}

fd_set TCPHandler::getMasterFd() const
{
	return this->_masterFd;
}

std::vector<int> TCPHandler::getFdServers() const
{
	return this->_fdServers;
}

std::vector<int> &TCPHandler::getFdClients() const
{
	return this->_fdClients;
}

int TCPHandler::getNbOfServer() const
{
	return this->_nbOfServer;
}

std::vector<Server> TCPHandler::getTabServers() const
{
	return this->_servers;
}

// ##################################################################
//                            Methodes                              #
// ##################################################################

// SERVEUR###########################################################
void TCPHandler::initServer()
{

	int serverSocket = 0;

	std::cout << std::endl;
	std::cout << COLOR_GREEN << "INIT SERVER\t\t\t" << getCurrentTimestamp() <<  COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN << "│" << COLOR_RESET << " Server listen on Port                             " << COLOR_GREEN << "│" << COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN << "│" << COLOR_RESET << "                                                   " << COLOR_GREEN << "│" << COLOR_RESET << std::endl;
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		it->setServerSocket(it->Init()); // init server
		serverSocket = it->getServerSocket();
		if (serverSocket < 0)
			exit(0);
		this->_fdServers.push_back(serverSocket);
		if (serverSocket > this->_maxFd)
			this->_maxFd = serverSocket;
		it->setServerSocket(serverSocket);

		std::cout << COLOR_GREEN << "│ " << COLOR_RESET << " * [Port: " << it->getPort() << "]" << " -> "  << "[Server Socket: " << serverSocket << "]\t\t\t" << COLOR_GREEN << "│" << COLOR_RESET << std::endl;
	}
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
}

void TCPHandler::runServer()
{
	bool running = true;
	int socketCount = 0;

	g_tcpHandlerInstance = this;
	signal(SIGINT, globalSignalHandler);

	std::cout << COLOR_GREEN << "SERVER RUN\t\t\t" << getCurrentTimestamp() << COLOR_RESET << std::endl;
	while (running)
	{
		setupMasterFd();
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
		std::cout << COLOR_YELLOW << "SOCKET STATE\t\t\t" << getCurrentTimestamp() << COLOR_RESET << std::endl;
		std::cout << COLOR_YELLOW << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &_masterFd))
			{
				std::cout << COLOR_YELLOW << "│" << COLOR_RESET << " Socket [" << i << "] is open \t\t\t\t     " << COLOR_YELLOW << "│" << COLOR_RESET << std::endl;
			}
		}
		std::cout << COLOR_YELLOW << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
		std::cout << "" << std::endl;
		fd_set copyW = _masterFd;
		fd_set copyR = _masterFd;
		//socketCount = select(_maxFd + 1, &copyW, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture (les sockets sont tjrs prete pour l ecriture), exceptions, delai d'attente
		socketCount = select(_maxFd + 1, &copyW, &copyR, NULL, NULL); // numero du fd le + eleve, lecture, ecriture (les sockets sont tjrs prete pour l ecriture), exceptions, delai d'attente
		if (socketCount == -1)
			std::cerr << "Error : SocketCount " << std::endl;
		for (int i = 0; i <= _maxFd; i++)
		{
			if (FD_ISSET(i, &copyW))
			{
				handlingNewClient(i); // accept new client
			}
			if (FD_ISSET(i, &copyW))
			{
				handlingCommunication(i); // recv n send data
			}
		}
	}
}

int TCPHandler::setupMasterFd()
{
	FD_ZERO(&_masterFd);

	std::vector<int> fdServers = getFdServers();
	for (std::vector<int>::iterator it = fdServers.begin(); it != fdServers.end(); ++it)
	{
		FD_SET(*it, &_masterFd);
	}

	std::vector<int> fdClients = getFdClients();
	for (std::vector<int>::iterator it = fdClients.begin(); it != fdClients.end(); ++it)
	{
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		if (getsockname(*it, (struct sockaddr *)&addr, &len) == 0)
		{
			FD_SET(*it, &_masterFd);
		}
	}
	return (0);
}

int TCPHandler::closeFd()
{
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		std::cout << COLOR_YELLOW << "CLOSING Server Socket "
				  << "[" << it->getServerSocket() << "]" << COLOR_RESET << std::endl;
		if (close(it->getServerSocket()) == -1)
		{
			std::cerr << "Error closing fd 2" << std::endl;
		}
	}
	std::vector<int> fdClients = getFdClients();
	for (size_t i = 0; i < fdClients.size(); i++)
	{
		std::cout << COLOR_YELLOW << "CLOSING Client Socket " << fdClients[i] << COLOR_RESET << std::endl;
		close(fdClients[i]);
	}
	return (0);
}

// CLIENTS###########################################################
int TCPHandler::handlingNewClient(int i)
{
	std::cout << COLOR_RED << "NEW CONNECTION 🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻" << COLOR_RESET << std::endl;
	std::cout << "" << std::endl;
	std::cout << COLOR_BLUE << "Handling New Client\t\t   " << getCurrentTimestamp() << COLOR_RESET << std::endl;
	std::cout << COLOR_BLUE << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	bool clientConnected = false;
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		if (i == it->getServerSocket())
		{
			int newClientFD = createNewClient(it->getServerSocket());
			if (newClientFD != -1) // Assurez-vous que createNewClient retourne le FD du nouveau client ou -1 en cas d'échec
			{
				std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "New client connected                              " << COLOR_BLUE << "│" << COLOR_RESET << std::endl;
				clientConnected = true;
				break; // Sortir de la boucle si un client a été connecté
			}
		}
	}
	if (!clientConnected)
	{
		std::cout << "│ No new client was connected                       │" << std::endl;
	}
	std::cout << COLOR_BLUE << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	return (0);
}

int TCPHandler::createNewClient(int socketServer)
{
	Client newClient;
	newClient.fillInfo(socketServer, this->_servers);
	_clients[newClient.getSocketClient()] = newClient;
	std::cout << COLOR_BLUE << "│ Create New Client:\t\t\t\t\t " << COLOR_BLUE << "│" << COLOR_RESET << std::endl;
	std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "BIND: "<< "Socket client: " << "[" << newClient.getSocketClient() << "]" << " Server Socket: " << "[" << newClient.getServerSocketAssociated() << "]\t" << COLOR_BLUE << "│" << COLOR_RESET << std::endl;
	_fdClients.push_back(newClient.getSocketClient());
	if (newClient.getSocketClient() == -1)
	{
		std::cerr << "Error in accepting client";
	}
	if (newClient.getSocketClient() > _maxFd)
		_maxFd = newClient.getSocketClient();
	return (0);
}

int TCPHandler::clientIsDisconnected(Client &client)
{
	if(client.getSocketClient() > 3)
	{
		if (close(client.getSocketClient()) == -1)
		{
			perror("fd");
			std::cerr << "Error closing fd 4" << std::endl;
		}
	}
	for (std::vector<int>::iterator it = _fdClients.begin(); it != _fdClients.end();)
	{
		if (*it == client.getSocketClient())
		{
			it = _fdClients.erase(it);
		}
		else
			++it;
	}
	FD_ZERO(&_masterFd);
	std::cout << COLOR_BLUE << "Client Socket [" << client.getSocketClient() << "]"<< COLOR_RED << " disconnected\t\t" << COLOR_RESET << getCurrentTimestamp() << COLOR_RESET << std::endl;
	return (0);
}

// Request and Response##############################################
int TCPHandler::handlingRequest(Client &client)
{
	int reading = 0;
	std::string buffer;
	char tmp[BUFFER_SIZE];
	ServerConfig &test = this->_servers[client.getServerIdx()].getServerConfigRef();

	do
	{
		memset(tmp, 0, sizeof(tmp));									   // Clear the buffer
		reading = recv(client.getSocketClient(), tmp, sizeof(tmp) - 1, 0); // Leave space for null terminator
		if (reading > 0)
		{
			buffer.append(tmp, reading);
		}
		else if (reading == 0)
		{
			std::cerr << "Client closed connection" << std::endl;
			return (0);
		}
		else
		{
			std::cerr << "Error recv" << std::endl;
			this->_servers[client.getServerIdx()].setStatusCode(500);
			clientIsDisconnected(client);
			return (-1);
		}
	} while (reading > 0 && buffer.find("\r\n\r\n") == std::string::npos);

	Response response(buffer, test);
	_response = response;

	return (reading);
}

int TCPHandler::handlingResponse(Client &client)
{
	int res = send(client.getSocketClient(), _response.getResponse().c_str(), _response.getResponse().size(), 0);

	if (res == -1)
	{
		std::cerr << "Error send" << std::endl;
		this->_servers[client.getServerIdx()].setStatusCode(500);
		clientIsDisconnected(client);
		return -1;
	}
	else if (res == 0)
	{
		std::cerr << "No data sent" << std::endl;
		clientIsDisconnected(client);
		return -1;
	}
	clientIsDisconnected(client);
	return (0);
}

int TCPHandler::handlingCommunication(int i)
{
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		if (_clients.count(i) > 0) // verif si cle i existe
		{
			if (i != it->getServerSocket())
			{
				Client &client = _clients[i]; // recup valeur se trouvnt a la cle i
				int reading = handlingRequest(client);
				it->setReading(reading);

				if (it->getReading() <= 0)
					clientIsDisconnected(client);
				else
					handlingResponse(client);
				break;
			}
		}
	}
	return (0);
}

void globalSignalHandler(int signal)
{
	if (signal == SIGINT)
	{
		if (g_tcpHandlerInstance != NULL)
			g_tcpHandlerInstance->closeFd();
	}
	exit(0);
}
