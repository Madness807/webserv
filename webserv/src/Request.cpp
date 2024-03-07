#include "../include/Request.hpp"
#include <iostream>

// Méthodes///////////////////
void Request::postMethod(){
    _method = "POST";
}
void Request::deleteMethod(){
    _method = "DELETE";
}
std::string Request::getMethod(){
    return _method;
}

// Constructeur
Request::Request()
{
    std::cout << "Constructeur de Request" << std::endl;
}
// Destructeur
Request::~Request(){
    std::cout << "Destructeur de Request" << std::endl;
}