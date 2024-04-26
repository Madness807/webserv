#include "../../include/Server/Server.hpp"

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
Server::Server(){}

Server::~Server(){}

Server::Server(std::string ipAdress, int port, ServerConfig conf, int idx) :_port(port),  _ipAdress(ipAdress), _idx(idx)
{
	_serverSocket = 0;
	_newSocket = 0;
	_opt = 1;
	_reading = 0;
	_socketCount = 0;
	_addr.sin_family = AF_INET;
	_serverConfig = conf;

	int result = inet_pton(AF_INET, _ipAdress.c_str(), &_addr.sin_addr); // converti une adresse IP de la forme texte ("127.0.0.1") en une forme binaire structurée que les fonctions de réseau peuvent utiliser.
	if (result == 0)
	{
		std::cerr << "Error : " << _ipAdress << "' is a invalid IPv4 adress." << std::endl;
	}
	else if (result < 0)
	{
		std::cerr << "IPv4 error conversion." << std::endl;
	}
	_addr.sin_port = htons(_port);
}

//##################################################################
//		constructeur par copie et operateur d'affectation		   #
//##################################################################
Server::Server(const Server &other) {
	*this = other;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other) {
		_port = other._port;
		_ipAdress = other._ipAdress;
		_idx = other._idx;
		_opt = other._opt;
		_serverSocket = other._serverSocket;
		_newSocket = other._newSocket;
		_socketCount = other._socketCount;
		_buffer = other._buffer;
		_file = other._file;
		_reading = other._reading;
		_serverConfig = other._serverConfig;
		_addr = other._addr;
	}
	return *this;
}

//##################################################################
//                          SETTERS                                #
//##################################################################
void Server::setFile(std::string file){
	this->_file = file;
}

void Server::setServerSocket(int serverSocket){
	this->_serverSocket = serverSocket;
}

void Server::setReading(int reading){
	this->_reading = reading;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
std::string Server::getFile() const{
	return this->_file;
}

int Server::getServerSocket() const{
	return this->_serverSocket;
}

int Server::getPort() const{
	return this->_port;
}

std::string Server::getIpAdress() const{
	return this->_ipAdress;
}

std::string Server::getBuffer() const{
	return this->_buffer;
}

int Server::getReading() const{
	return this->_reading;
}

ServerConfig& Server::getServerConfigRef() const{
	ServerConfig& ref = const_cast<ServerConfig&>(this->_serverConfig);
	ref = this->_serverConfig;
	return ref;
}

ServerConfig Server::getServerConfig() const{
	return this->_serverConfig;
}

int Server::getIdx(){
	return this->_idx;
}

//##################################################################
//                           Methodes                              #
//##################################################################
int Server::Init()
{
	// socket creation
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	if (_serverSocket == -1)
	{
		std::cerr << "Error: Server socket creation failed" << std::endl;
		exit(-1);
	}
	// option to prevent error "address already in use”."
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt)) < 0) {
		std::cerr << "Error: Server setsockopt failed" << std::endl;
		exit(-1);
	}
	// bind the socket to an address
	if (bind(_serverSocket, (sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		perror("bind failed");
		std::cerr << "Error: Bind failed" << std::endl;
		exit(-1);
	}
	if(listen(_serverSocket, 25) < 0)// mettre variable pour waiting list
	{
		std::cerr << "Error: Listen failed" << std::endl;
		exit(-1);
	}
	return (_serverSocket);
}

void Server::sendToClient(int clientSocket, const char* message, int messageSize)
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

