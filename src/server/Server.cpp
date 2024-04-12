#include "../../include/Server/Server.hpp"
#include "../../include/client/Client.hpp"

#include "../../include/Response/Response.hpp"

Server::Server(){
	_serverSocket = 10;
	_newSocket = 0;
	_opt = 1;
	_reading = 0;
	_socketCount = 0;
	_addr.sin_family = AF_INET;
	_buffer = "";

	//_addr.sin_addr.s_addr = INADDR_ANY; INADDR_ANY == localhost
	int result = inet_pton(AF_INET, _ipAdress.c_str(), &_addr.sin_addr); // converti une adresse IP de la forme texte ("127.0.0.1") en une forme binaire structurée que les fonctions de réseau peuvent utiliser.
	// socketpair htons, htonl, ntohs, ntohl
	if (result == 0) {
        std::cerr << "Erreur : l'adresse '" << _ipAdress << "' n'est pas une adresse IPv4 valide." << std::endl;
    } else if (result < 0) {
        std::cerr << "Erreur lors de la conversion de l'adresse IPv4 : " << strerror(errno) << std::endl;
    }

	_addr.sin_port = htons(_port);
}

Server::~Server(){
}

Server::Server(std::string ipAdress, int port) :_port(port),  _ipAdress(ipAdress)
{
	_serverSocket = 20;
	_newSocket = 0;
	_opt = 1;
	_reading = 0;
	_socketCount = 0;
	_addr.sin_family = AF_INET;

	//_addr.sin_addr.s_addr = INADDR_ANY; INADDR_ANY == localhost
	int result = inet_pton(AF_INET, _ipAdress.c_str(), &_addr.sin_addr); // converti une adresse IP de la forme texte ("127.0.0.1") en une forme binaire structurée que les fonctions de réseau peuvent utiliser.
	// socketpair htons, htonl, ntohs, ntohl
	if (result == 0) {
        std::cerr << "Erreur : l'adresse '" << _ipAdress << "' n'est pas une adresse IPv4 valide." << std::endl;
    } else if (result < 0) {
        std::cerr << "Erreur lors de la conversion de l'adresse IPv4 : " << strerror(errno) << std::endl;
    }

	_addr.sin_port = htons(_port);
	//std::cout << "Server created with ip : " << _ipAdress << " on port : " << _port  << std::endl;
	//_addr.sin_addr.s_addr = htonl(_ipAdress);
}

Server::Server(const Server &other) {
	*this = other;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other) {
		_serverSocket = other._serverSocket;
		_newSocket = other._newSocket;
		_port = other._port;
		_ipAdress = other._ipAdress;
		_addr = other._addr;
	}
	return *this;
}

int Server::Init()
{

	// socket creation
	// -> int sockfd = socket(domain, type, protocol)
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	if (_serverSocket == -1)
	{
		std::cerr << "Error: server socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	// option to prevent error "address already in use”."
	// -> int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen); // permet de reutiliser le port
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt)) < 0) {
		perror("setsockopt");
		std::cerr << "Error: server setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// bind the socket to an address
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if (bind(_serverSocket, (sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		perror("bind");
		std::cerr << "Error: bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if(listen(_serverSocket, 1) < 0)// mettre variable pour waiting list
	{
		std::cerr << "Error: listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	//std::cout << "serversocket dans init server : " << _serverSocket << std::endl;
	//FD_ZERO(&_masterFdRead);
	//FD_ZERO(&_masterFdWrite);
	//FD_SET(_serverSocket, &_masterFdRead); // ajoute un fd a un ensemble de fd, en lien avec select, ajoute _serverSocket a _masterFd

	return (_serverSocket);
}

void Server::sendToClient(int clientSocket, const char* message, int messageSize)// send message to client
{
	send(clientSocket, message, messageSize, 0);
}

void Server::onClientConnected(int clientSocket)
{
	std::string message = "Welcome to the server\n";
	sendToClient(clientSocket, message.c_str(), message.size() + 1);
}

void Server::onClientDisconnected(int clientSocket)
{
	std::string message = "Goodbye\n";
	sendToClient(clientSocket, message.c_str(), message.size() + 1);
}

std::string Server::getFile() const
{
	return this->_file;
}

void Server::setFile(std::string file)
{
	this->_file = file;
}

std::string Server::getResponse() const
{
	return this->_response;
}

void Server::setResponse(std::string response)
{
	this->_response = response;
}

int Server::getServerSocket() const
{
	return this->_serverSocket;
}

void Server::setServerSocket(int serverSocket)
{
	this->_serverSocket = serverSocket;
}

int Server::getPort() const
{
	return this->_port;
}

std::string Server::getIpAdress() const
{
	return this->_ipAdress;
}

std::string Server::getBuffer() const
{
	return this->_buffer;
}

void Server::setReading(int reading)
{
	this->_reading = reading;
}

int Server::getReading() const
{
	return this->_reading;
}


