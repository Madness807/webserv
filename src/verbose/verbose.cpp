#include "../include/verbose/verbose.hpp"
#include "../include/define.hpp"

void printAllSrvConfig(ServerManager *serverManager)
{
    std::vector<ServerConfig> servers = serverManager->getServerConfig(); // récupérer la liste des serveurs

    for (size_t i = 0; i < servers.size(); ++i)
    {
        const ServerConfig& serverConfig = servers[i];
        // imprimer les informations de chaque serveur
        std::cout << COLOR_RED << "┌SERVER CONFIG ───────────────────────────────────────────────" << COLOR_RESET << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "Name:\t\t\t" << serverConfig.getServerName() << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "IP:\t\t\t" << serverConfig.getIp() << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "Port:\t\t\t" << serverConfig.getPort() << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "Max Body Size:\t" << serverConfig.getMaxBodySize() << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "Default File:\t\t" << serverConfig.getDefaultFile() << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "Error Page:\t\t" << serverConfig.getErrorPage() << std::endl;
        std::cout << COLOR_RED << "│ " << COLOR_RESET << "Root:\t\t\t" << serverConfig.getRoot() << std::endl;
		std::cout << ""<< std::endl;

        std::map<std::string, LocationConfig> locations = serverConfig.getMapLocation();
        for (std::map<std::string, LocationConfig>::const_iterator it = locations.begin(); it != locations.end(); ++it)
        {
            const LocationConfig& locationConfig = it->second;
            std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Location:\t\t" << locationConfig.getPath() << std::endl;
            std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Redirection:\t\t" << locationConfig.getRedirect() << std::endl;
            if (locationConfig.getDirectoryListing())
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Directory Listing:\t" << "ON" << std::endl;
            else
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Directory Listing:\t" << "OFF" << std::endl;
            if (locationConfig.getCgiPath().empty())
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Cgi Path:\t\t" << "OFF" << std::endl;
            else
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Cgi Path:\t\t" << locationConfig.getCgiPath() << std::endl;
            if (locationConfig.getCgiExtension().empty())
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Cgi Extension:\t" << "OFF" << std::endl;
            else
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Cgi Extension:\t\t" << locationConfig.getCgiExtension() << std::endl;
            std::vector<std::string> methods = locationConfig.getMethods();
            for (size_t j = 0; j < methods.size(); ++j)
            {
                std::cout << COLOR_BLUE << "│ " << COLOR_RESET << "Methods:\t\t" << methods[j] << std::endl;
            }
            std::cout << std::endl; // Espace entre les serveurs pour une meilleure lisibilité
        }
    }
}
