#include "../include/ConfigParser/LocationConfig.hpp"

//Méthodes
//GETTERS
std::string location::getPath(){
    return _path;
}
std::vector<std::string> location::getMethods(){
    return _methods;
}
std::string location::getRedirect(){
    return _redirect;
}

//SETTERS
void location::setPath(std::string path){
    _path = path;
}
void location::setMethods(std::vector<std::string> methods){
    _methods = methods;
}
void location::setRedirect(std::string redirect){
    _redirect = redirect;
}

// constructeur
LocationConfig::LocationConfig() {
}
// destructeur
LocationConfig::~LocationConfig() {
}
