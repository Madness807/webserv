#include "../include/Client.hpp"

Client::Client() {
	_opt = 1;
	_socketClient = 0;
	_testClient = "salut from client";
}

Client::Client(int ipAdress, int port) : _serverPort(port), _serverIpAdress(ipAdress) {
	_socketClient = 0;
	_opt = 1;
	_reading = 0;
	_testClient = "salut from client";
	_addrServer.sin_family = AF_INET;
	_addrServer.sin_port = htons(_serverPort);
	_addrServer.sin_addr.s_addr = htonl(_serverIpAdress);
}

Client::~Client() {
}

Client::Client(const Client &other) {
	*this = other;
}

Client &Client::operator=(const Client &other) {
	if (this != &other) {
	}
	return *this;
}

int Client::Init() {
	// socket creation
	// -> int sockfd = socket(domain, type, protocol)
	_socketClient = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	if (_socketClient == -1) {
		std::cerr << "Error: client socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	// socket option
	// -> int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen); // permet de reutiliser le port
	if (setsockopt(_socketClient, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt)) < 0) {
	 	std::cerr << "Error: client setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	// Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &_addrServer.sin_addr)
        <= 0) {
        std::cerr << "\nInvalid address/ Address not supported" << std::endl;
        return -1;
    }

	return 0;
}

int Client::Run() {
	const char* cstr = _testClient.c_str();
	//int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// connect to the server
	if (connect(_socketClient, (struct sockaddr *)&_addrServer, sizeof(_addrServer)) < 0) {
		std::cerr << "Error: connection failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ((connect(_socketClient, (struct sockaddr*)&_addrServer, sizeof(_addrServer))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(_socketClient, cstr, strlen(cstr), 0);
    std::cout << "Hello message sent, client" << std::endl;
    _reading = read(_socketClient, _buffer, 1024 - 1); // subtract 1 for the null terminator at the end
    std::cout << _buffer << std::endl;

    // closing the connected socket
    close(_socketClient);
	return 0;
}

