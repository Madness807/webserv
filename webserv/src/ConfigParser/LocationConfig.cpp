#include "../../include/ConfigParser/LocationConfig.hpp"

//##################################################################
//                          SETTERS                                #
//##################################################################
void LocationConfig::setPath(std::string path) {
    _path = path;
}
void LocationConfig::setMethods(std::vector<std::string> methods) {
    _methods = methods;
}
void LocationConfig::setRedirect(std::string redirect) {
    _redirect = redirect;
}
void LocationConfig::setDirectoryListing(bool directory_listing) {
    _directory_listing = directory_listing;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
std::string LocationConfig::getPath() {
    return _path;
}
std::string LocationConfig::getRedirect() {
    return _redirect;
}
bool LocationConfig::getDirectoryListing() {
    return _directory_listing;
}
std::vector<std::string> LocationConfig::getMethods() {
    return _methods;
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
}
LocationConfig::~LocationConfig() {
}
