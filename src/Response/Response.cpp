#include "../../include/Response/Response.hpp"

// Méthodes
// GETTERS
// SETTERS


// Constructeur
Response::Response(std::string &str): _request(str), _statusCode(200), _statusMessages(setStatusMessages()), _statusMessage("")
{
    if (_request.getRet() != 200)
        this->setStatusCode(_request.getRet());
    // else if (_server.getRet() != 200)
    //     this->setStatusCode(_server.getRet());
    else
        this->setStatusCode(200);
}
// Destructeur
Response::~Response() {}

void    Response::setStatusCode(const int &code)
{
    _statusCode = code;
    _statusMessage = this->getStatusMessage(code);
    if (code != 200)
    {
        std::cout << COLOR_RED << "\n\n\n\n################################### CRITICAL ERROR ###################################\n\n" << COLOR_RESET;
        std::cout << "This computer will" << COLOR_RED << " self-destruct " << COLOR_RESET << "in 10 seconds..." << std::endl;
        sleep(3);
        std::cout << "\n9..\n" << std::endl;
        sleep(1);
        std::cout << "8..\n" << std::endl;
        sleep(1);
        std::cout << "7..\n" << std::endl;
        sleep(1);
        std::cout << "6..\n" << std::endl;
        sleep(1);
        std::cout << "5..\n" << std::endl;
        sleep(1);
        std::cout << "4..\n" << std::endl;
        sleep(1);
        std::cout << "3..\n" << std::endl;
        sleep(1);
        std::cout << "2..\n" << std::endl;
        sleep(1);
        std::cout << "1..\n" << std::endl;
        sleep(5);
        std::cout << "\n\n\n\n\nJust Fucking Kidding !!! x)\n\n\n\n" << std::endl;
    }
}

std::map<int, std::string>    Response::setStatusMessages()
{
    std::map<int, std::string>  messages;
    messages[200] = "OK";
    messages[400] = "Bad Request";
    messages[403] = "Forbidden";
    messages[404] = "Not Found";
    messages[405] = "Method Not Allowed";
    messages[410] = "Gone";
    messages[413] = "Payload To Large";
    messages[500] = "Internal Server Error";
    return (messages);
}

int Response::getStatusCode() const
{
    return (_statusCode);
}

std::string Response::getStatusMessage(const int &code)
{
    std::map<int, std::string>::iterator it = _statusMessages.find(code);
    if (it != _statusMessages.end())
        return (it->second);
    else
        return ("Error");
}


/*
Response.cpp
Rôle: Construit la réponse HTTP à envoyer au client.
Fonctions:
    Permet de construire une réponse HTTP, incluant le statut, les en-têtes, et le corps de la réponse.
    Offre des méthodes pour ajouter des en-têtes, définir le corps de la réponse, et éventuellement gérer les types de contenu MIME.
    Génère la réponse finale sous forme de chaîne ou de bytes à envoyer sur le réseau.
*/