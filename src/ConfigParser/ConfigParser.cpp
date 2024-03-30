#include "../include/ConfigParser/ConfigParser.hpp"
#include "../include/ConfigParser/ServerConfig.hpp"
#include "../include/ConfigParser/LocationConfig.hpp"

//##################################################################
//                          GETTERS                                #
//##################################################################
ServerConfig* parsingSrvConf::getServerConfig(const std::string& ip, int port) {
    for (ServerConfig& config : _serverConfigs) {
        if (config.getIp() == ip && config.getPort() == port) {
            return &config; // Retourne l'adresse de la configuration trouvée
        }
    }
    return nullptr; // Retourne nullptr si aucune configuration correspondante n'est trouvée
}



//##################################################################
//                          Methodes                               #
//##################################################################
void parsingSrvConf::parseServerConfig(std::string line)//
{
    if (line.find("server_name") != std::string::npos) {
        _serverConfig->setServerName(line.substr(line.find("server_name") + 12, line.find(":") - line.find("server_name") - 13));
    }
    else if (line.find("ip") != std::string::npos) {
        _serverConfig->setIp(line.substr(line.find("ip") + 4, line.find(":") - line.find("ip") - 4));
    }
    else if (line.find("port") != std::string::npos) {
        _serverConfig->setPort(line.substr(line.find("port") + 5, line.find(":") - line.find("port") - 6));
    }
    else if (line.find("max_body_size") != std::string::npos) {
        _serverConfig->setMaxBodySize(line.substr(line.find("max_body_size") + 15, line.find(":") - line.find("max_body_size") - 15));
    }
    else if (line.find("default_file") != std::string::npos) {
        _serverConfig->setDefaultFile(line.substr(line.find("default_file") + 12, line.find(":") - line.find("default_file") - 13));
    }
    else if (line.find("error_page") != std::string::npos) {
        _serverConfig->setErrorPage(line.substr(line.find("error_page") + 11, line.find(":") - line.find("error_page") - 12));
    }
    else if (line.find("root") != std::string::npos) {
        _serverConfig->setRoot(line.substr(line.find("root") + 6, line.find(":") - line.find("root") - 7));
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

void parsingSrvConf::readConfigFile(std::string filename)//lecture du fichier de configuration
{
    std::ifstream configFile(filename);//ouverture du fichier
    if (!configFile.is_open())//si le fichier n'est pas ouvert
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }
    std::string line;//variable pour stocker les lignes du fichier
    LocationConfig location = LocationConfig();//variable pour stocker les locations
    while (std::getline(configFile, line))//tant qu'il y a des lignes dans le fichier
    {
        if (line.find("server") != std::string::npos)//si la ligne contient le mot "server"
        {
            while (std::getline(configFile, line))//tant qu'il y a des lignes dans le fichier
            {
                if (line.find("ServerConfig_start") != std::string::npos)//si la ligne contient le mot "ServerConfig_start"
                {   
                    while (line.find("ServerConfig_end") == std::string::npos)//
                    {
                        std::getline(configFile, line);//on lit la ligne suivante
                        parseServerConfig(line);//on parse la ligne
                    }
                }

                if (line.find("location_start") != std::string::npos)//si la ligne contient le mot "location_start"
                {
                    location = LocationConfig();
                    while (std::getline(configFile, line))//tant qu'il y a des lignes dans le fichier
                    {
                        if (line.find("location_end") != std::string::npos)//si la ligne contient le mot "location_end"
                        {
                            _serverConfig->addLocation(location.getPath() ,location);
                            break;//on sort de la boucle
                        }
                        parseLocationConfig(line, location);//on parse la ligne 
                    }                
                }
                
            }
        }
    }
    configFile.close();//fermeture du fichier
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
parsingSrvConf::parsingSrvConf() {
    _serverConfig = new ServerConfig();
}
parsingSrvConf::parsingSrvConf(const parsingSrvConf& other) {
    _serverConfig = new ServerConfig(*other._serverConfig);
}
parsingSrvConf::~parsingSrvConf() {
    delete _serverConfig;
}
