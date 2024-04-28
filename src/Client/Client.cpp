#include "../../include/client/Client.hpp"

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
Client::Client() : _socketClient(0), _clientRequete(""), _clientReponse(""), _buffer(""){}

Client::~Client() {}

//##################################################################
//		constructeur par copie et operateur d'affectation		   #
//##################################################################
Client::Client(const Client &other) {
	*this = other;}

Client &Client::operator=(const Client &other) {
	if (this != &other) {
		this->_idxServer = other._idxServer;
		this->_socketClient = other._socketClient;
		this->_serverSocketAssociated = other._serverSocketAssociated;
		this->_clientRequete = other._clientRequete;
		this->_clientReponse = other._clientReponse;
		this->_buffer = other._buffer;
		this->_addrClient = other._addrClient;
		this->_addrClientSize = other._addrClientSize;
	}
	return *this;}

//##################################################################
//                          SETTERS                                #
//##################################################################
void Client::setSocketClient(int socketClient){
	this->_socketClient = socketClient;
}

void Client::setServerSocketAssociated(int serverSocket){
	this->_serverSocketAssociated = serverSocket;
}

void Client::setBuffer(std::string message){
	this->_buffer = message;
}

void Client::setAddrClientSize(socklen_t size){
	this->_addrClientSize = size;
}

void Client::setAddrClient(struct sockaddr_in addrClient){
	this->_addrClient = addrClient;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
int Client::getSocketClient() const{
	return this->_socketClient;
}
int Client::getServerSocketAssociated() const{
	return this->_serverSocketAssociated;
}
std::string Client::getBuffer() const{
	return this->_buffer;
}
const struct sockaddr_in& Client::getAddrClient() const{
	return this->_addrClient;
}
socklen_t Client::getAddrClientSize() const{
	return sizeof(this->_addrClient);
}

int Client::getServerIdx() const{
	return this->_idxServer;
}

//##################################################################
//                           Methodes                              #
//##################################################################
int Client::fillInfo(int serverSocket, std::vector<Server> &server){

	for (std::vector<Server>::iterator it = server.begin(); it != server.end(); ++it)
	{
		if (it->getServerSocket() == serverSocket)
		{
			_idxServer = it->getIdx();
		}
	}
	socklen_t clientSize = this->getAddrClientSize();
	int socketClient = accept(serverSocket, (sockaddr*)&this->getAddrClient(), &clientSize);
	if (socketClient == -1)
	{
		std::cerr << "Error accepting new cient" << std::endl;
		server[_idxServer].setStatusCode(500);
		return (-1);
	}
	if (fcntl(socketClient, F_SETFL, O_NONBLOCK) == -1)
	{
    	perror("fcntl");
	}
	this->setSocketClient(socketClient);
	this->setAddrClientSize(clientSize);
	this->setServerSocketAssociated(serverSocket);

	return (0);
}
