#include "../include/Server.hpp"

//INADDR_ANY == localhost

Server::Server(){
}

Server::~Server(){
}

Server::Server(const char* ipAdress, int port) :_port(port),  _ipAdress(ipAdress)
{
	_serverSocket = 0;
	_newSocket = 0;
	_opt = 1;
	_reading = 0;

	_addr.sin_family = AF_INET;

	//_addr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, _ipAdress, &_addr.sin_addr); // converti une adresse IP de la forme texte ("127.0.0.1") en une forme binaire structurée que les fonctions de réseau peuvent utiliser.

	_addr.sin_port = htons(_port);
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
	if (_serverSocket == -1) // == INVALID_SOCKET
	{
		std::cerr << "Error: server socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// option to prevent error "address already in use”."
	// -> int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen); // permet de reutiliser le port
	// if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt)) < 0) {
	// 	std::cerr << "Error: server setsockopt failed" << std::endl;
	// 	exit(EXIT_FAILURE);
	// }

	// bind the socket to an address
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if (bind(_serverSocket, (sockaddr *)&_addr, sizeof(_addr)) < 0) // == SOCKET_ERROR
	{
		std::cerr << "Error: bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if(listen(_serverSocket, 3) < 0) // == SOCKET_ERROR
	{
		std::cerr << "Error: listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	FD_ZERO(&_masterFd); // initialise a 0 masterFD, en lien avec select
	FD_SET(_serverSocket, &_masterFd); // ajoute un fd a un ensemble de fd, en lien avec select, ajoute _serverSocket a _masterFd

	/*
		Ces ensembles de descripteurs de fichiers sont ensuite utilisés avec la fonction `select`, qui peut surveiller plusieurs descripteurs de fichiers pour voir s'ils sont prêts pour la lecture, l'écriture ou si une exception s'est produite.
	*/

	return (0);
}

int Server::Run()
{
	bool running = true;
	int max_sd = _serverSocket;

	while (running)
	{
		fd_set copy = _masterFd;
		// See who's talking to us
		int socketCount = select(max_sd + 1, &copy, nullptr, nullptr, nullptr); // pour gerer plusieurs fd, pour voir si il y a des data a lire, si on peut ecrire et si il y a des exceptions

		// Loop through all the current connections / potential connect
		for (int i = 0; socketCount > 0; i++)
		{
			if (FD_ISSET(i, &copy))
			{
				if (i == _serverSocket)
				{
					sockaddr_in client;
					socklen_t clientSize = sizeof(client);
					int clientSocket = accept(_serverSocket, (sockaddr*)&client, &clientSize);
					if (clientSocket == -1)
					{
						std::cerr << "Error in accepting client";
					}
					if (clientSocket > 0)
					{
						FD_SET(clientSocket, &_masterFd);
						onClientConnected(clientSocket);
					}
					else // It's an inbound message
					{
						//char buf[4096];
						memset(_buffer, 0, sizeof(_buffer));
				// Receive message
			//	int bytesIn = recv(sock, buf, 4096, 0);
						int bytesIn = recv(i, _buffer, sizeof(_buffer), 0);
						if (bytesIn <= 0)
						{
						// Drop the client
							onClientDisconnected(i);
							close(i);
							FD_CLR(i, &_masterFd);
						// client is disconnected
						}
						else
						{
							std::cout << "Received: \n" << _buffer << std::endl;
	//onMessageReceived(i, _buffer, bytesIn);
					// Check to see if it's a command. \quit kills the server
					// if (_buffer[0] == '\\')
					// {
					// 	// Is the command quit?
					// 	std::string cmd = std::string(_buffer, bytesIn);
					// 	if (cmd == "\\quit")
					// 	{
					// 		running = false;
					// 		break;
					// 	}

					// 	// Unknown command
					// 	//continue;
					// }

					// Send message to other clients, and definiately NOT the listening socket

					//else
					//{
							for (int j = 0; j <= max_sd; ++j)
							{
								if (FD_ISSET(j, &_masterFd) && j != _serverSocket && j != i)
								{
									//(j, _buffer, bytesIn, 0);
									onMessageReceived(j, _buffer, bytesIn);
								}
							}
						}
					}
				}
				--socketCount;
			}
		}
	}

	close(_serverSocket);
	while (FD_ISSET(_serverSocket, &_masterFd)) {
		FD_CLR(_serverSocket, &_masterFd);
	}

	return 0;
}

	//int listen(int sockfd, int backlog); // met le socket en mode ecoute, backlog = nombre de connexions en attente

	//int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	/*It extracts the first connection request on the queue of pending connections for the listening socket,
	sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
	*/
// 	_newSocket = accept(_serverSocket, (struct sockaddr *)NULL, NULL); // lier la socket du client
// 	if (_newSocket < 0) {
// 		std::cerr << "Error: accept failed" << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	//At this point, the connection is established between client and server, and they are ready to transfer data.
// 	_reading = read(_newSocket, _buffer, 1024 - 1);
// 	send(_newSocket, cstr, strlen(cstr), 0);
//     std::cout << "Hello message sent, server" << std::endl;
// 	close(_newSocket);
// 	close(_serverSocket);
// 	return(0);
// }


/*
ecoute sur les ports specifiés dans le fichier de configuration
accepte les connexions entrantes et cree des objets de type Request pour chaque requete recu
utilise des objets de type Response pour repondre aux requetes
gere la logique de selection/polling pour traiter les connexions de maniere non bloquante
*/



void Server::sendToClient(int clientSocket, const char* message, int messageSize)// send message to client
{
	send(clientSocket, message, messageSize, 0);
}

void Server::sendToAllClients(int sendingClientSocket, const char* message, int messageSize) // send message to all clients
{
	fd_set copy = _masterFd;
	int max_sd = _serverSocket;

	int socketCount = select(max_sd + 1, &copy, nullptr, nullptr, nullptr);

	for (int i = 0; socketCount > 0; i++)
	{
		if (FD_ISSET(i, &copy))
		{
			if (i != _serverSocket && i != sendingClientSocket)
			{
				sendToClient(i, message, messageSize);
			}
		}
		--socketCount;
	}
}

void Server::onMessageReceived(int clientSocket, const char* message, int messageSize)
{
	(void)clientSocket;
	(void)messageSize;
	(void)message;
	std::cout << "Server ft: Received: \n" << message << std::endl;
	//broadcast(clientSocket, message, messageSize);
}
void Server::onClientConnected(int clientSocket)
{
	(void)clientSocket;
}

void Server::onClientDisconnected(int clientSocket)
{
	(void)clientSocket;
}
