#ifndef CONFIGSRVCONF_HPP
#define CONFIGSRVCONF_HPP

#include <string>
#include <map>
#include <list>

class ServerConfig{
    private:
        std::string _server_name;
        std::string _ip;
        std::string _port;
        std::string _max_body_size;

    public:
        // constructeur et destructeur
            ServerConfig();
            ~ServerConfig();

        // Méthodes///////////////////
        // SETTERS
        void setServerName(std::string server_name);
        void setPort(std::string port);
        void setIp(std::string ip);
        void setMaxBodySize(std::string max_body_size);
        // GETTERS
        std::string getServerName();
        std::string getPort();
        std::string getIp();
        std::string getMaxBodySize();

};

#endif