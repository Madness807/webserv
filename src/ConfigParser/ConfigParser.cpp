#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../include/ConfigParser/LocationConfig.hpp"
#include "../include/ConfigParser/ServerManager.hpp"

//##################################################################
//                          GETTERS                                #
//##################################################################
ServerConfig* parsingSrvConf::getServerConfig(const std::string& ip, int port) {
	return _serverManager.getServerConfig(ip, port);
}

//##################################################################
//                          Methodes                               #
//##################################################################

void parsingSrvConf::parseServerConfig(std::string line, ServerConfig& serverConfig)//
{
	if (line.find("server_name") != std::string::npos) {
		serverConfig.setServerName(line.substr(line.find("server_name") + 12, line.find(":") - line.find("server_name") - 13));
	}
	else if (line.find("ip") != std::string::npos) {
		serverConfig.setIp(line.substr(line.find("ip") + 4, line.find(":") - line.find("ip") - 4));
	}
	else if (line.find("port") != std::string::npos) {
		serverConfig.setPort(line.substr(line.find("port") + 5, line.find(":") - line.find("port") - 6));
	}
	else if (line.find("max_body_size") != std::string::npos) {
		serverConfig.setMaxBodySize(line.substr(line.find("max_body_size") + 15, line.find(":") - line.find("max_body_size") - 15));
	}
	else if (line.find("default_file") != std::string::npos) {
		serverConfig.setDefaultFile(line.substr(line.find("default_file") + 12, line.find(":") - line.find("default_file") - 13));
	}
	else if (line.find("error_page") != std::string::npos) {
		serverConfig.setErrorPage(line.substr(line.find("error_page") + 11, line.find(":") - line.find("error_page") - 12));
	}
	else if (line.find("root") != std::string::npos) {
		serverConfig.setRoot(line.substr(line.find("root") + 6, line.find(":") - line.find("root") - 7));
	}
}

LocationConfig parsingSrvConf::parseLocationConfig(std::string line, LocationConfig& location)
{
	if (line.find("path") != std::string::npos)
	{   
		location.setPath(line.substr(line.find("path") + 6, line.find(":") - line.find("path") - 6));
	}
	else if (line.find("redirect") != std::string::npos)
	{
		location.setRedirect(line.substr(line.find("redirect") + 10, line.find(":") - line.find("redirect") - 10));
	}
	else if (line.find("methods") != std::string::npos)
	{
		std::string methodsSubstr = line.substr(line.find("methods") + 9 , line.find(":") - line.find("methods") - 9);
		methodsSubstr.erase(0, methodsSubstr.find_first_not_of(" "));
		std::stringstream ss(methodsSubstr);
		std::string method;
		std::vector<std::string> methods;
		 
		while (std::getline(ss, method, ','))
		{
			method.erase(0, method.find_first_not_of(" "));
			method.erase(method.find_last_not_of(" ") + 1);
			methods.push_back(method);
		}
		location.setMethods(methods);
		}
		else if (line.find("directory_listing") != std::string::npos)
		{
			location.setDirectoryListing(false);
		}
	return (location);
}

void parsingSrvConf::readConfigFile(std::string filename)
{
	std::ifstream configFile(filename);
	if (!configFile.is_open())
	{
		std::cerr << "Error: could not open file " << filename << std::endl;
		return;
	}
	std::string line;
	ServerConfig currentServerConfig;
	LocationConfig location;
	bool inServerConfig = false;
	bool inLocationConfig = false;

	while (std::getline(configFile, line))
	{
		line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

		if (line.find("server_start") != std::string::npos)
		{
			currentServerConfig = ServerConfig();
			inServerConfig = true;
		}
		else if (line.find("server_end") != std::string::npos)
		{
			_serverManager.addServerConfig(currentServerConfig.getIp(), currentServerConfig.getPort(), currentServerConfig);
			inServerConfig = false;
		}
		else if (inServerConfig)
		{
			if (line.find("location_start") != std::string::npos)
			{
				location = LocationConfig();
				inLocationConfig = true;
			}
			else if (line.find("location_end") != std::string::npos)
			{
				currentServerConfig.addLocation(location.getPath() ,location);
				inLocationConfig = false;
			}
			else if (inLocationConfig)
			{
				parseLocationConfig(line, location);
			}
			else
			{
				parseServerConfig(line, currentServerConfig);
			}
		}
	}
	configFile.close();//fermeture du fichier
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
parsingSrvConf::parsingSrvConf() {
}
parsingSrvConf::parsingSrvConf(const parsingSrvConf& other) {
}
parsingSrvConf::~parsingSrvConf() {
}


// todo
// Ajustements Basés sur la Discussion :
// Passer de std::list<ServerConfig> à une structure de données qui fournit un accès plus rapide et permet une recherche basée sur une clé unique. Cela pourrait être une std::map avec une paire IP-port comme clé.
// Assurer que le ServerManager dispose de méthodes appropriées pour ajouter, récupérer et supprimer des configurations de serveur basées sur la paire IP-port.
// Mettre à jour le parsingSrvConf pour utiliser ServerManager lors de l'ajout de nouvelles configurations de serveur après les avoir parsées.
// Veiller à une bonne validation des données du fichier de configuration et à la gestion des erreurs potentielles.
// En suivant ces points basés sur notre discussion, votre conception et votre code seront alignés pour gérer efficacement les configurations de serveur de votre projet Webserv.