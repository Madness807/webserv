#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>
#include <map>
#include <vector>

class LocationConfig{
    private:
        std::string _path;
        std::vector<std::string> _methods;
        std::string _redirect;
        bool _directory_listing;

    public:

        // constructeur et destructeur
            LocationConfig();
            ~LocationConfig();

        // Méthodes///////////////////
        // SETTERS
        void setPath(std::string path);
        void setMethods(std::vector<std::string> methods);
        void setRedirect(std::string redirect);
        void setDirectoryListing(bool directory_listing);
        // GETTERS
        std::string getPath();
        std::vector<std::string> getMethods();
        std::string getRedirect();
        bool getDirectoryListing();
        
};

#endif