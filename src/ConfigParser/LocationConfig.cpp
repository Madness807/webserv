#include "../../include/ConfigParser/LocationConfig.hpp"

//##################################################################
//                          SETTERS                                #
//##################################################################
void LocationConfig::setPath(std::string path) {
    path = trim(path);
    if (path.empty())
    {
        std::cerr << "Error: Path: empty path" << std::endl;
        exit (1);
    }
    _path = path;
}
void LocationConfig::setMethods(std::vector<std::string> methods) {
    _methods = methods;
}
void LocationConfig::setRedirect(std::string redirect) {
    redirect = trim(redirect);
    if (redirect.empty())
    {
        std::cerr << "Error: Redirect: empty redirect" << std::endl;
        exit (1);
    }
    _redirect = redirect;
}
void LocationConfig::setDirectoryListing(bool directory_listing) {
    _directory_listing = directory_listing;
}
void LocationConfig::setCgiPath(std::string path) {
    cgiPath = path;
}
void LocationConfig::setCgiExtension(std::string extension) {
    cgiExtension = extension;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
std::string LocationConfig::getPath() const{
    return _path;
}
std::string LocationConfig::getRedirect() const{
    return _redirect;
}
bool LocationConfig::getDirectoryListing() const{
    return _directory_listing;
}
std::vector<std::string> LocationConfig::getMethods() const{
    return _methods;
}
std::string LocationConfig::getCgiPath() const{
    return cgiPath;
}
std::string LocationConfig::getCgiExtension() const{
    return cgiExtension;
}

//##################################################################
//                          Methodes                               #
//##################################################################
void LocationConfig::addMethod(std::string method) {
    _methods.push_back(method);
}

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
LocationConfig::LocationConfig() {
    _path = "";
    _redirect = "";
    _directory_listing = false;
    _methods = std::vector<std::string>();
    cgiPath = "Not set";
    cgiExtension = "Not set";
}
LocationConfig::~LocationConfig() {
}
