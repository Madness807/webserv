#include "../include/client/Client.hpp"

Client::Client() : _socketClient(0), _clientRequete(""), _clientReponse(""){
	memset(_buffer, 0, sizeof(_buffer));
	(void)_socketClient;
}

Client::~Client() {}

Client::Client(const Client &other) {
	*this = other;
}

Client &Client::operator=(const Client &other) {
	if (this != &other) {
	}
	return *this;
}

void Client::setRequete(std::string requete)
{
	this->_clientRequete = requete;
}

std::string Client::getRequete() const
{
	return this->_clientRequete;
}

void Client::setReponse(std::string reponse)
{
	this->_clientReponse = reponse;
}

std::string Client::getReponse() const
{
	return this->_clientReponse;
}

int Client::getSocketClient() const
{
	return this->_socketClient;
}
