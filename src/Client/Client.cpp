#include "../include/client/Client.hpp"
#include <string>
#include <iostream>

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
// void Client::setRequete(std::string requete){
// 	this->_clientRequete = requete;
// }

// void Client::setReponse(std::string reponse){
// 	this->_clientReponse = reponse;
// }

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
// std::string Client::getRequete() const{
// 	return this->_clientRequete;
// }
// std::string Client::getReponse() const{
// 	return this->_clientReponse;
// }
int Client::getSocketClient() const{
	return this->_socketClient;
}
int Client::getServerSocketAssociated() const{
	return this->_serverSocketAssociated;
}
std::string Client::getBuffer() const{
	//std::string str(this->_buffer[BUFFER_SIZE - 1]);
	return this->_buffer;
}
const struct sockaddr_in& Client::getAddrClient() const{
	return this->_addrClient;
}
socklen_t Client::getAddrClientSize() const{
	return sizeof(this->_addrClient);
}

//##################################################################
//                           Methodes                              #
//##################################################################
void Client::fillInfo(int serverSocket){

	socklen_t clientSize = this->getAddrClientSize();
	std::cout << "Client size accepting: " << clientSize << std::endl;
	int socketClient = accept(serverSocket, (sockaddr*)&this->getAddrClient(), &clientSize); // accept
	//std::cout << "clientClass > client socket : " << socketClient << std::endl;
	std::cout << "Client size accepted: " << clientSize << std::endl;
	this->setSocketClient(socketClient);
	this->setAddrClientSize(clientSize);
	this->setServerSocketAssociated(serverSocket);
}
