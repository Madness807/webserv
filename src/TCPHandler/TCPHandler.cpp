#include "../include/TCPHandler/TCPHandler.hpp"
#include <fcntl.h>
#include <ctime>

TCPHandler* g_tcpHandlerInstance = NULL;
void globalSignalHandler(int signal);

std::string getCurrentTimestamp() {
	char buffer[20];
	time_t now = time(0);
	struct tm *timeinfo = localtime(&now);

	// Format: YYYY-MM-DD HH:MM:SS
	strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", timeinfo);

	return std::string(buffer);
}

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
	int count = 0;

	for(std::vector<ServerConfig>::const_iterator it = serverConfigs.begin(); it != serverConfigs.end(); ++it)
	{
		Server newserver(it->getIp(), it->getPort(), *it, count);
		count++;
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

//SERVEUR###########################################################
void TCPHandler::initServer() {

	int serverSocket = 0;

		std::cout << std::endl;
	std::cout << COLOR_GREEN << "INIT SERVER\t\t\t[" << getCurrentTimestamp() << "]" << COLOR_RESET << std::endl;
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

		std::cout << COLOR_GREEN << "│" << COLOR_RESET
				  << " -> [Port: " << it->getPort() << "] [FD: " << serverSocket << "]     "
				  //< std::string(43 - 16 - std::to_string(it->getPort()).length() - std::to_string(serverSocket).length(), ' ') // Calculer l'espacement
				  << COLOR_GREEN << "│" << COLOR_RESET << std::endl;
	}
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
}

void TCPHandler::runServer()
{
	bool running = true;
	int socketCount = 0;

	g_tcpHandlerInstance = this;
	signal(SIGINT, globalSignalHandler);

	std::cout << COLOR_GREEN << "SERVER RUN\t\t\t[" << getCurrentTimestamp() << "]" << COLOR_RESET << std::endl;
	while (running)
	{
		setupMasterFd();
		std::cout << std::endl;
		std::cout << COLOR_YELLOW << "MASTER FD STATE\t\t\t[" << getCurrentTimestamp() << "]" << COLOR_RESET << std::endl;
		std::cout << COLOR_YELLOW << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &_masterFd))
			{
				std::cout << COLOR_YELLOW << "│" << COLOR_RESET << " FD [" << i << "] is open \t\t\t\t    " << COLOR_YELLOW << "│" << COLOR_RESET << std::endl;
			}
		}
		std::cout << COLOR_YELLOW << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
		fd_set copyW = _masterFd;
		//fd_set copyR = _masterFd;
		socketCount = select(_maxFd + 1, &copyW, NULL, NULL, NULL); // numero du fd le + eleve, lecture, ecriture (les sockets sont tjrs prete pour l ecriture), exceptions, delai d'attente
		if (socketCount == -1)
			std::cerr << "Error : SocketCount " << std::endl;
		std::cout << "socketCount : " << socketCount << std::endl;
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

//FILE DESCRIPTOR###################################################
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

int TCPHandler::closeFd() {

	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		std::cout << COLOR_YELLOW <<"CLOSING -> it->getServerSocket() : " << it->getServerSocket() << COLOR_RESET << std::endl;
		close(it->getServerSocket());
	}
	std::vector<int>fdClients = getFdClients();
	for (size_t i = 0; i < fdClients.size(); i++)
	{
		std::cout << COLOR_YELLOW << "CLOSING -> fdClients[i] : " << fdClients[i] << COLOR_RESET << std::endl;
		close(fdClients[i]);
	}
	return(0);
}

//CLIENTS###########################################################
int TCPHandler::handlingNewClient(int i)
{
	std::cout << COLOR_BLUE << "TCPHandler::handlingNewClient\t[" << getCurrentTimestamp() << "]" << COLOR_RESET << std::endl;
	std::cout << COLOR_BLUE << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	bool clientConnected = false;
	for(std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		if (i == it->getServerSocket())
		{
			int newClientFD = createNewClient(it->getServerSocket());
			if (newClientFD != -1) // Assurez-vous que createNewClient retourne le FD du nouveau client ou -1 en cas d'échec
			{
				std::cout << "│ New client connected                              " << COLOR_BLUE << "│" << COLOR_RESET << std::endl;
				clientConnected = true;
				break; // Sortir de la boucle si un client a été connecté
			}
		}
	}
	if (!clientConnected){
		std::cout << COLOR_BLUE << "│ No new client was connected                       │" << COLOR_RESET << std::endl;
	}
	std::cout << COLOR_BLUE << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	return (0);
}

int TCPHandler::createNewClient(int socketServer)
{
	Client newClient;
	newClient.fillInfo(socketServer, this->_servers);
	_clients[newClient.getSocketClient()] = newClient;
	std::cout << COLOR_BLUE << "| TCPHandler::createNewClient:\t\t\t    " << COLOR_BLUE << "│" << COLOR_RESET << std::endl;
	std::cout << "| BIND FD: " << "[" <<newClient.getSocketClient() << "]" << " Socket: " << "[" << newClient.getServerSocketAssociated() << "]\t\t\t    "<< COLOR_BLUE << "│" << COLOR_RESET << std::endl;
	_fdClients.push_back(newClient.getSocketClient());
	if(newClient.getSocketClient() == -1)
	{
		std::cerr << "Error in accepting client";
	}
	if(newClient.getSocketClient() > _maxFd)
		_maxFd = newClient.getSocketClient();
	return(0);
}

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

//Request and Response##############################################
int TCPHandler::handlingRequest(Client &client)
{
	int reading = 0;
<<<<<<< HEAD
	std::string buffer2;
	char tmp[BUFFER_SIZE];
	ServerConfig& test = this->_servers[client.getServerIdx()].getServerConfigRef();
=======
	std::string buffer;
	//std::cout << ">> client socket : " << client.getSocketClient() << std::endl;
	char tmp[BUFFER_SIZE];
	memset(tmp, 0, sizeof(tmp));
	//std::cout << "SERVER SOCKET : " << client.getServerSocketAssociated() << std::endl;
	buffer = &tmp[0];
	// Response response(buffer, _serverManager.getServerConfig());
	Response response(buffer, this->_servers[client.getServerSocketAssociated()].getServerConfigRef());
	_response = response;
	reading = recv(client.getSocketClient(), tmp, sizeof(tmp), 0);
>>>>>>> origin/main

	do {
		memset(tmp, 0, sizeof(tmp)); // Clear the buffer
		reading = recv(client.getSocketClient(), tmp, sizeof(tmp) - 1, 0); // Leave space for null terminator
		if (reading > 0) {
			buffer2.append(tmp, reading);
		}
		if (reading < 0)
		{
			std::cerr << "Error recv" << std::endl;
			clientIsDisconnected(client);
			return (-1);
		}

	} while (reading > 0 && buffer2.find("\r\n\r\n") == std::string::npos);

	Response response(buffer2, test);
	_response = response;

	return(reading);
}

int TCPHandler::handlingResponse(Client &client)// c est cella qui marche si jamais
{
	// std::string test = _serverManager.getServerConfig("127.0.0.1", 8888)->getDefaultFile();
	// std::string toto = "website/page" + test;

	// std::ifstream file(getFile().c_str());
	//std::ifstream file("/Users/jdefayes/documents/git/Cursus/webserv/website/bali_m.jpg.image.694.390.low.jpg");
<<<<<<< HEAD
	//std::ifstream file(toto.c_str());
	//std::ifstream file(*ServerConfig.getPath());

	//std::stringstream buffer;
	//buffer << file.rdbuf();
	//std::cout << "buffer: " << buffer.str() << std::endl;

	//std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
	//std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg

	//std::string response = getResponse() + buffer.str();
	std::cout << "response : " << _response.getResponse() << std::endl;
	if (send(client.getSocketClient(), _response.getResponse().c_str(), _response.getResponse().size(), 0) == -1)
	{
		std::cerr << "Error send" << std::endl;
		clientIsDisconnected(client);
		return (-1);
	}

=======
	// std::ifstream file(toto);
	//std::ifstream file(*ServerConfig.getPath());

	// std::stringstream buffer;
	// buffer << file.rdbuf();
	//std::cout << "buffer: " << buffer.str() << std::endl;

	//std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n" + buffer.str();
	// std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + buffer.str(); // regarder meme types des fichiers, text/html, image/jpeg

	//std::string response = getResponse() + buffer.str();
	// std::cout << "reponse" << response.c_str() << std::endl;
	std::cout << _response.getResponse() << std::endl;
	send(client.getSocketClient(), _response.getResponse().c_str(), _response.getResponse().size(), 0);
>>>>>>> origin/main

	clientIsDisconnected(client);
	//client.setSocketClient(-1);
	//std::string response = getResponse() + buffer.str();
	//send(client.getSocketClient(), response.c_str(), response.length(), 0);
	std::cout << COLOR_YELLOW << "Closing fd client" << COLOR_RESET << std::endl;
	//close(client.getSocketClient());

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

// A trier ou a supprimer###########################################
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

void globalSignalHandler(int signal) {
	if (signal == SIGINT)
	{
		if(g_tcpHandlerInstance != NULL)
			g_tcpHandlerInstance->closeFd();
	}
	exit(0);
}
