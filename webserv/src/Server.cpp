#include "../include/Server.hpp"

Server::Server(){
}

Server::~Server(){
}

Server::Server(int ipAdress, int port) : _port(port), _ipAdress(ipAdress) {
	_serverSocket = 0;
	_newSocket = 0;
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = htonl(_ipAdress);
}

Server::Server(const Server &other) {
	*this = other;
}

Server &Server::operator=(const Server &other) {
	if (this != &other) {
		_serverSocket = other._serverSocket;
		_newSocket = other._newSocket;
		_port = other._port;
		_ipAdress = other._ipAdress;
		_addr = other._addr;
	}
	return *this;
}

int Server::Init() {
	int opt = 1;
	std::string test = "salut from server";
	// socket creation
	// -> int sockfd = socket(domain, type, protocol)
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	if (_serverSocket == -1) {
		std::cerr << "Error: socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// option to prevent error "address already in use”."
	// -> int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen); // permet de reutiliser le port
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
		std::cerr << "Error: setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// bind the socket to an address
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if (bind(_serverSocket, (struct sockaddr *)&_addr, sizeof(_addr)) < 0) {
		std::cerr << "Error: bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	return (0);
}

int Server::Run() {
	//int listen(int sockfd, int backlog); // met le socket en mode ecoute, backlog = nombre de connexions en attente
	if(listen(_serverSocket, 3) < 0) {
		std::cerr << "Error: listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	//int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	/*It extracts the first connection request on the queue of pending connections for the listening socket,
	sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
	At this point, the connection is established between client and server, and they are ready to transfer data.*/
	_newSocket = accept(_serverSocket, (struct sockaddr *)NULL, NULL);
	if (_newSocket < 0) {
		std::cerr << "Error: accept failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	//At this point, the connection is established between client and server, and they are ready to transfer data.

	//int close(int sockfd);
	return(0);
}


/*
ecoute sur les ports specifiés dans le fichier de configuration
accepte les connexions entrantes et cree des objets de type Request pour chaque requete recu
utilise des objets de type Response pour repondre aux requetes
gere la logique de selection/polling pour traiter les connexions de maniere non bloquante
*/
