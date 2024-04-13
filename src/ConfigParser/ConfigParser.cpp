#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../include/ConfigParser/LocationConfig.hpp"
#include "../include/ConfigParser/ServerManager.hpp"

//##################################################################
//                          Methodes                               #
//##################################################################

void parsingSrvConf::parseServerConfig(std::string line, ServerConfig& serverConfig)
{
	if (line.find("server_name") != std::string::npos) {
		serverConfig.setServerName(line.substr(line.find(":") + 1));
	}
	else if (line.find("ip") != std::string::npos) {
		serverConfig.setIp(line.substr(line.find(":") + 1));
	}
	else if (line.find("port") != std::string::npos) {
		serverConfig.setPort(line.substr(line.find(":") + 1));
	}
	else if (line.find("max_body_size") != std::string::npos) {
		serverConfig.setMaxBodySize(line.substr(line.find(":") + 1));
	}
	else if (line.find("default_file") != std::string::npos) {
		serverConfig.setDefaultFile((line.substr(line.find(":") + 1)));
	}
	else if (line.find("error_page") != std::string::npos) {
		serverConfig.setErrorPage((line.substr(line.find(":") + 1)));
	}
	else if (line.find("root") != std::string::npos) {
		serverConfig.setRoot((line.substr(line.find(":") + 1)));
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

std::vector<ServerConfig> parsingSrvConf::readConfigFile(std::string filename)
{
	std::ifstream configFile(filename);
	if (!configFile.is_open())
	{
		std::cerr << "Error: could not open file " << filename << std::endl;
		return std::vector<ServerConfig>();
	}
	std::string line;
	std::vector<ServerConfig> serverConfigs;
	ServerConfig currentServerConfig;
	LocationConfig location;
	bool inServerConfig = false;
	bool inLocationConfig = false;

	while (std::getline(configFile, line))
	{
		line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

		if (line.empty())
			continue;
		if (line.find("server_start") != std::string::npos)
		{
			currentServerConfig = ServerConfig();
			inServerConfig = true;
		}
		else if (line.find("server_end") != std::string::npos)
		{
			serverConfigs.push_back(currentServerConfig);
			inServerConfig = false;
			currentServerConfig = ServerConfig();
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
			else if (inLocationConfig){
				parseLocationConfig(line, location);
			}
			else if (inServerConfig){
				parseServerConfig(line, currentServerConfig);
			}
		}
	}
	configFile.close();
	return serverConfigs;
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
parsingSrvConf::parsingSrvConf() {
}
parsingSrvConf::~parsingSrvConf() {
}
