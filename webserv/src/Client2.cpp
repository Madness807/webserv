#include "../include/Client2.hpp"

void Client2::onClientConnected(int clientSocket)
{
	std::string message = "Welcome to the server\n";
	sendToClient(clientSocket, message.c_str(), message.size() + 1);
}

void Client2::onClientDisconnected(int clientSocket)
{
	std::string message = "Goodbye\n";
	sendToClient(clientSocket, message.c_str(), message.size() + 1);
}

void Client2::onMessageReceived(int clientSocket, const char* message, int messageSize) // gestion de message recu d un client
{
//	(void)clientSocket;
//	(void)messageSize;
	std::cout << "Received: \n" << message << std::endl;
	sendToAllClients(clientSocket, message, messageSize);
}
