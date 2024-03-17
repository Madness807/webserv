#ifndef CONFIGSRVCONF_HPP
#define CONFIGSRVCONF_HPP

#include <string>
#include <map>
#include <list>

class parsingSrvConf{
    private:
    
    public:
        // constructeur et destructeur
            parsingSrvConf();
            ~parsingSrvConf();

        // Méthodes///////////////////
        void readConfigFile(std::string filename);

        // GETTERS
        // SETTERS
        void setServerName(std::string server_name);
        void setPort(std::string port);
        void setIp(std::string ip);
        void setMaxBodySize(std::string max_body_size);


};

#endif