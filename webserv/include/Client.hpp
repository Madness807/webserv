#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ConfigParser.hpp"
#include "Connection.hpp"
#include "ConfigParser.hpp"
#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

class Client
{
    private:
        int _socketClient;
        int _opt;
        int _serverPort;
        const char* _serverIpAdress;
        size_t _reading;
        std::string _buffer[1024];
        struct sockaddr_in _addrServer;
        std::string _testClient;

    public:
        // constructeur et destructeur
        Client();
        Client(const char* ipAdress, int port);
        ~Client();
        Client(const Client &other);
        Client &operator=(const Client &other);

        int Init();
        int Run();

        // Méthodes///////////////////
        // GETTERS
        // SETTERS

};

#endif

// 	bool running = true;
// 	while (running)
// 	{
// 		fd_set copy = master;
// 		int socketCount = select(max_sd + 1, &copy, nullptr, nullptr, nullptr);
// 		for (int i = 0; i <= max_sd && socketCount > 0; ++i)
// 		{
// 			if (FD_ISSET(i, &copy))
// 			{
// 				if (i == listening)
// 				{
// 					sockaddr_in client;
// 					socklen_t clientSize = sizeof(client);
// 					int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

// 					if (clientSocket == -1)
// 					{
// 						cerr << "Error in accepting client";
// 					}
// 					else
// 					{
// 						FD_SET(clientSocket, &master);
// 						if (clientSocket > max_sd)
// 						{
// 							max_sd = clientSocket;
// 						}
// 						cout << "New connection from " << inet_ntoa(client.sin_addr) << ", port " << ntohs(client.sin_port) << endl;
// 					}
// 				}
// 				else
// 				{
// 					char buf[4096];
// 					memset(buf, 0, sizeof(buf));
// 					int bytesIn = recv(i, buf, sizeof(buf), 0);
// 					if (bytesIn <= 0)
// 					{
// 						close(i);
// 						FD_CLR(i, &master);
// 					}
// 					else
// 					{
// 						if (buf[0] == '\\')
// 						{
// 							string cmd = string(buf, bytesIn);
// 							if (cmd == "\\quit")
// 							{
// 								running = false;
// 								break;
// 							}
// 						}
// 						else
// 						{
// 							for (int j = 0; j <= max_sd; ++j)
// 							{
// 								if (FD_ISSET(j, &master) && j != listening && j != i)
// 								{
// 									send(j, buf, bytesIn, 0);
// 								}
// 							}
// 						}
// 					}
// 				}
// 				--socketCount;
// 			}
// 		}
// 	}

// 	close(listening);
// 	while (FD_ISSET(listening, &master))
// 	{
// 		FD_CLR(listening, &master);
// 	}

// 	return 0;
// }
