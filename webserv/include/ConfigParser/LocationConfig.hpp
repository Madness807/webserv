#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>
#include <map>
#include <list>
#include <vector>

class location{
    private:
        std::string _path;
        std::vector<std::string> _methods;
        std::string _redirect;
        //bool _directory_listing;

    public:

        // constructeur et destructeur
            location();
            ~location();

        // Méthodes///////////////////
        // GETTERS
        // SETTERS
};

#endif