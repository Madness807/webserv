#include "../include/Server.hpp"
#include "ConfigParser.hpp"
#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

class Client2 : public Server
{
	public :
	Client2(const char* ipAdress, int port):
		Server(ipAdress, port){}

	protected:
 		virtual void onClientConnected(int clientSocket);
   	 	virtual void onClientDisconnected(int clientSocket);
   	 	virtual void onMessageReceived(int clientSocket, const char* message, int messageSize); // gestion de message recu d un client
};
