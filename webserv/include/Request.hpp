#include <iostream>

class Request {
public:
    private:
    std::string _method;
    
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