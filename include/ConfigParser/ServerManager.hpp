#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include "../define.hpp"
#include "ServerConfig.hpp"
#include "ConfigParser.hpp"

class ServerManager{
	private:
		std::vector<ServerConfig> _configs;

	public:
		// constructeur et destructeur
		ServerManager();
		ServerManager(std::string filename);
		~ServerManager();

	// Méthodes pour gérer les configurations de serveur
		void addServerConfig(const std::string& ip, int port, const ServerConfig& config);
		void removeServerConfig(const std::string& ip, int port);

	// Setters
		void setServerConfig(std::string filename);

	// Getters
		const std::vector<ServerConfig> getServerConfig() const;
		ServerConfig* getServerConfig(const std::string& ip, int port);


	};

#endif

