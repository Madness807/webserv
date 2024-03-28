#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>

class Request {
    private:
    std::string _method;
    
    public:
    // Constructeur et destructeur
    Request();
    ~Request();

    // Méthodes///////////////////
    // Setters
    void postMethod();
    void deleteMethod();
    // Getters
    std::string getMethod();
};

#endif
