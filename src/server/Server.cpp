#include "../../include/Server/Server.hpp"
#include "../../include/client/Client.hpp"

Server::Server(){
}

Server::~Server(){
}

Server::Server(std::string ipAdress, int port) :_port(port),  _ipAdress(ipAdress)
{
	_serverSocket = 0;
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

	FD_ZERO(&_masterFdRead);
	FD_ZERO(&_masterFdWrite);
	FD_SET(_serverSocket, &_masterFdRead); // ajoute un fd a un ensemble de fd, en lien avec select, ajoute _serverSocket a _masterFd

	return (0);
}

int Server::Run()
{
	bool running = true;
	int max_sd = _serverSocket;
	std::vector<Client> clients(100);

	std::cout << "Server is running" << std::endl;
	while (running)
	{
		fd_set copy = _masterFdRead;
		// See who's talking to us
		_socketCount = select(max_sd + 1, &copy, NULL, NULL, NULL); // pour gerer plusieurs fd, pour voir si il y a des data a lire, si on peut ecrire et si il y a des exceptions

		// Loop through all the current connections / potential connect
		for (int i = 0; i <= max_sd; i++) //(int i = 0; _socketCount > 0; i++)
		{
			if (FD_ISSET(i, &copy) && i == _serverSocket)
			{
				int socketClient = 0;
				//sockaddr_in client;

				//socklen_t clientSize = sizeof(client);
				//int clientSocket = accept(_serverSocket, (sockaddr*)&client, &clientSize);
				//socklen_t clientAddrSize = clients[i].getAddrClientSize();

				socklen_t clientSize = clients[i].getAddrClientSize();
				clients[i].setAddrClientSize(clientSize);

				socketClient = accept(_serverSocket, (sockaddr*)&clients[i].getAddrClient(), &clientSize);
				clients[i].setSocketClient(socketClient, clientSize);
				//clients[i].setSocketClient(socketClient) = accept(_serverSocket, (sockaddr*)&clients[i].getAddrClient(), &clients[i].getAddrClientSize());
				if(socketClient == -1) //if (clientSocket == -1)
				{
					std::cerr << "Error in accepting client";
				}
				if(socketClient > max_sd)//if (clientSocket > max_sd)
				{
        			max_sd = socketClient;
    			}
				std::cout << "socket client: " << clients[i].getSocketClient() << std::endl;
				FD_SET(clients[i].getSocketClient(), &_masterFdRead);
				if (socketClient > 0)
				{
					onClientConnected(socketClient);
				}
				break;
			}
			if (FD_ISSET(i, &copy) && i != _serverSocket)
			{
				memset(_buffer, 0, sizeof(_buffer));
				_reading = recv(i, _buffer, sizeof(_buffer), 0);
				//std::cout << "Received: " << _buffer << std::endl;
				if (_reading <= 0)
				{
					close(i);
					FD_CLR(i, &_masterFdRead);
					onClientDisconnected(i);
				}
				else
				{
					//setBuffer(i, _buffer);
					this->sendToClient(i, _buffer, _reading);
					//std::cout << "getBuffer: " << getBuffer(i) << std::endl;
				}
				break;
			}
		}
	}

	while (FD_ISSET(_serverSocket, &_masterFdRead))
	{
		FD_CLR(_serverSocket, &_masterFdRead);
	}
	close(_serverSocket);
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

void Server::sendToAllClients(int sending_client, int max_sd, const char* message, int messageSize) // send message to all clients
{

	for (int i = 0; i <= max_sd; i++)
	{
		if (FD_ISSET(i, &_masterFdRead) && i != _serverSocket && i != sending_client)
		{
			send(i, message, messageSize, 0);
		}
	}
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

// • Il doit être non bloquant et n’utiliser qu’un seul poll() (SELECT) (ou équivalent) pour toutes les opérations entrées/sorties entre le client et le serveur (listen inclus).
// read/recv ou write/send
// si vous essayez d’utiliser read/recv ou write/send avec n’importe quel FD sans utiliser poll() (ou équivalent), votre note sera de 0.
// Votre serveur doit pouvoir écouter sur plusieurs ports (cf. Fichier de configuration).
// Vu que MacOS n’implémente pas write() comme les autres Unix, vous pouvez utiliser fcntl(). Vous devez utiliser des descripteurs de fichier en mode non bloquant afin d’obtenir un résultat similaire à celui des autres Unix
// Toutefois, vous ne pouvez utiliser fcntl() que de la façon suivante : F_SETFL, O_NONBLOCK et FD_CLOEXEC. Tout autre flag est interdit.

