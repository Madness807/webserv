#include "../include/TCPHandler/TCPHandler.hpp"
#include <fcntl.h>

TCPHandler* g_tcpHandlerInstance = NULL;
void globalSignalHandler(int signal);

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
TCPHandler::TCPHandler() : _response()
{
		FD_ZERO(&_masterFd);
		_maxFd = 0;
		_nbOfServer = 2;
}

TCPHandler::~TCPHandler() {}

//##################################################################
//		constructeur par copie et operateur d'affectation		   #
//##################################################################
TCPHandler::TCPHandler(const TCPHandler &other) {
	*this = other;
}

TCPHandler &TCPHandler::operator=(const TCPHandler &other) {
	if (this != &other) {
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

//##################################################################
//                          SETTERS                                #
//##################################################################
void TCPHandler::setMaxFd(int maxFd) {
	this->_maxFd = maxFd;
}

void TCPHandler::setMasterFd(fd_set masterFd) {
	this->_masterFd = masterFd;
}

void TCPHandler::setServerManager(ServerManager &serverManager) {
	this->_serverManager = serverManager;
}

void TCPHandler::setTabServers(ServerManager &server_manager)
{
	this->_serverManager = server_manager;
	std::vector<Server> servers;
	const std::vector<ServerConfig> serverConfigs = this->_serverManager.getServerConfig();

	for(std::vector<ServerConfig>::const_iterator it = serverConfigs.begin(); it != serverConfigs.end(); ++it)
	{
		Server newserver(it->getIp(), it->getPort(), *it);
		//std::cout << "CHECK " << newserver.getServerConfig().getIp() << " PORT: " << newserver.getServerConfig().getPort() << std::endl;
		servers.push_back(newserver);
	}

	this->_servers = servers;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
int TCPHandler::getMaxFd() const {
	return _maxFd;
}

fd_set TCPHandler::getMasterFd() const {
	return this->_masterFd;
}

std::vector<int> TCPHandler::getFdServers() const {
	return this->_fdServers;
}

std::vector<int> TCPHandler::getFdClients() const {
	return this->_fdClients;
}

int TCPHandler::getNbOfServer() const {
	return this->_nbOfServer;
}

std::vector<Server> TCPHandler::getTabServers() const {
	return this->_servers;
}

//##################################################################
//                           Methodes                              #
//##################################################################
void TCPHandler::initServer() {

	int serverSocket = 0;

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
	}
}

int TCPHandler::closeFd() {

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
	return(0);
}

void globalSignalHandler(int signal) {
	if (signal == SIGINT)
	{
		if(g_tcpHandlerInstance != NULL)
			g_tcpHandlerInstance->closeFd();
	}
	exit(0);
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
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		if (getsockname(*it, (struct sockaddr *)&addr, &len) == -1)
		{
			close(*it);
		}
		else
		{
			FD_SET(*it, &_masterFd);
		}
	}
	return (0);
}

void TCPHandler::runServer()
{
	bool running = true;
	int socketCount = 0;

	g_tcpHandlerInstance = this;
	signal(SIGINT, globalSignalHandler);

	while (running)
	{
		setupMasterFd();
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &_masterFd))
			{
				std::cout << "File descriptor " << i << " is in the set" << std::endl;
			}
		}

		fd_set *copy = &_masterFd;
		socketCount = select(_maxFd + 1, copy, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture, exceptions, delai d'attente
		if (socketCount == -1)
			std::cerr << "Error : SocketCount " << std::endl;
		for (int i = 0; i <= _maxFd; i++)
		{
			if (FD_ISSET(i, copy))
			{
				handlingNewClient(i); // accept new client
			}
			if (FD_ISSET(i, copy))
			{
				handlingCommunication(i); // recv n send data
			}
		}
	}
}

int TCPHandler::handlingNewClient(int i)
{
	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		std::cout << "handling new client (i == serversocket)i : " << i << " serverSocket : " << it->getServerSocket() << std::endl;
		if (i == it->getServerSocket())
		{
			std::cout << "i == serverSocket" << std::endl;
			createNewClient(it->getServerSocket());
			break;
		}
	}
	return (0);
}

int TCPHandler::createNewClient(int socketServer)
{
	Client newClient;
	newClient.fillInfo(socketServer);
	_clients[newClient.getSocketClient()] = newClient;
	std::cout << "-------- newClient.getSocketClient() : " << newClient.getSocketClient() << " sockerServer : " << newClient.getServerSocketAssociated() << std::endl;
	_fdClients.push_back(newClient.getSocketClient());
	if(newClient.getSocketClient() == -1)
	{
		std::cerr << "Error in accepting client";
	}

	if(newClient.getSocketClient() > _maxFd)
		_maxFd = newClient.getSocketClient();
	return(0);
}

int TCPHandler::handlingCommunication(int i)
{
	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		if (_clients.count(i) > 0) // verif si cle i existe
		{
			if (i != it->getServerSocket())
			{
				Client& client = _clients[i]; // recup valeur se trouvnt a la cle i
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

// int TCPHandler::handlingRequest(Client &client)
// {
//     int reading = 0;

//     //std::cout << ">> client socket : " << client.getSocketClient() << std::endl;
//     char tmp[BUFFER_SIZE];
//     std::string buffer;
//     memset(tmp, 0, sizeof(tmp));
//     reading = recv(client.getSocketClient(), tmp, sizeof(tmp), 0);
//     buffer = &tmp[0];
//     Response response(buffer, _servers[client.getServerSocketAssociated()].getServerConfigRef());
//     _response = &response;

//     //std::cout << "fdclient *_fdClients.begin() : " << *_fdClients.begin() << std::endl;
//     std::cout << "fdclient newClient.getSocketClient() : " << client.getSocketClient() << std::endl;
//     //it->setReading(reading);

//     //std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;
//     return(reading);
// }

int TCPHandler::handlingRequest(Client &client)
{
	int reading = 0;
	//std::string buffer;
	//std::cout << ">> client socket : " << client.getSocketClient() << std::endl;
	char tmp[BUFFER_SIZE];
	memset(tmp, 0, sizeof(tmp));
	//std::cout << "SERVER SOCKET : " << client.getServerSocketAssociated() << std::endl;
	//Response response(tmp, serverConfig);
	//buffer = &tmp[0];
	//Response response(buffer, &this->_servers[client.getServerSocketAssociated()].getServerConfig());
	//_response = response;
	reading = recv(client.getSocketClient(), tmp, sizeof(tmp), 0);

	//std::cout << "SERVER CONFIG : " << this->_servers[client.getServerSocketAssociated()].getServerConfig().getDefaultFile() << std::endl;

	//std::cout << "reading: " << reading << " it->reading : " << it->getReading() << std::endl;
	return(reading);
}

int TCPHandler::handlingResponse(Client &client)
{
	std::string test = _serverManager.getServerConfig("127.0.0.1", 8888)->getDefaultFile();
	std::string toto = "website" + test;

	// std::ifstream file(getFile().c_str());
	//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/bali_m.jpg.image.694.390.low.jpg");
	std::ifstream file(toto);
	//std::ifstream file(*ServerConfig.getPath());

	std::stringstream buffer;
	buffer << file.rdbuf();
	//std::cout << "buffer: " << buffer.str() << std::endl;

	//std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
	std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg

	//std::string response = getResponse() + buffer.str();
	send(client.getSocketClient(), response.c_str(), response.size(), 0);

	clientIsDisconnected(client);
	client.setSocketClient(-1);

	return(0);
}


// int TCPHandler::handlingResponse(Client &client)
// {
//     std::string test = _serverManager.getServerConfig("127.0.0.1", 8888)->getDefaultFile();
//     std::string toto = "website" + test;

//     // std::ifstream file(getFile().c_str());
//     //std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/bali_m.jpg.image.694.390.low.jpg");
//     std::ifstream file(toto);
//     //std::ifstream file(*ServerConfig.getPath());
//     std::stringstream buffer;
//     buffer << file.rdbuf();

//     //std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
//     // std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg

//     //std::string response = getResponse() + buffer.str();
//     send(client.getSocketClient(), _response->getResponse().c_str(), _response->getResponse().length(), 0);
//     std::cout << "Closing fd client" << std::endl;
//     close(client.getSocketClient());

//     client.setSocketClient(-1);
//     return(0);
// }

int TCPHandler::clientIsDisconnected(Client &client)
{
	close(client.getSocketClient());
	std::vector<int> fdClients = getFdClients();
	for (std::vector<int>::iterator it = fdClients.begin(); it != fdClients.end();)
	{
		if (*it == client.getSocketClient())
		{
			it = fdClients.erase(it);
		}
		else
			++it;
	}
	return (0);
}
