#ifndef CONFIGSRVCONF_HPP
#define CONFIGSRVCONF_HPP

#include <string>
#include <map>
#include <list>

class Serverconfig{
    private:
        std::string _server_name;
        std::string _port;
        std::string _ip;
        std::string _max_body_size;

    public:
        // constructeur et destructeur
            Serverconfig();
            ~Serverconfig();

        // Méthodes///////////////////
        // GETTERS
        // SETTERS
};

#endif