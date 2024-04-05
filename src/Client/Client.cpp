#include "../include/client/Client.hpp"
#include <string>
#include <iostream>

Client::Client() : _socketClient(0), _clientRequete(""), _clientReponse(""), _buffer(""){}

Client::~Client() {}

Client::Client(const Client &other) {
	*this = other;}

Client &Client::operator=(const Client &other) {
	if (this != &other) {
	}
	return *this;}

void Client::fillInfo(int serverSocket){

	socklen_t clientSize = this->getAddrClientSize();
	this->setAddrClientSize(clientSize);
	int socketClient = accept(serverSocket, (sockaddr*)&this->getAddrClient(), &clientSize); // accept
	this->setSocketClient(socketClient);
	this->setAddrClientSize(clientSize);
	this->setServerSocketAssociated(serverSocket);}

std::string Client::getRequete() const{
	return this->_clientRequete;}

void Client::setRequete(std::string requete){
	this->_clientRequete = requete;}


std::string Client::getReponse() const{
	return this->_clientReponse;}

void Client::setReponse(std::string reponse){
	this->_clientReponse = reponse;}


int Client::getSocketClient() const{
	return this->_socketClient;}

void Client::setSocketClient(int socketClient){
	this->_socketClient = socketClient;}

void Client::setServerSocketAssociated(int serverSocket){
	this->_serverSocketAssociated = serverSocket;}

int Client::getServerSocketAssociated() const{
	return this->_serverSocketAssociated;
}
std::string Client::getBuffer() const{
	//std::string str(this->_buffer[BUFFER_SIZE - 1]);
	return this->_buffer;}

void Client::setBuffer(std::string message){
	this->_buffer = message;}


socklen_t Client::getAddrClientSize() const{
	return sizeof(this->_addrClient);}

void Client::setAddrClientSize(socklen_t size){
	this->_addrClientSize = size;}


const struct sockaddr_in& Client::getAddrClient() const{
	return this->_addrClient;}

void Client::setAddrClient(struct sockaddr_in addrClient){
	this->_addrClient = addrClient;}
