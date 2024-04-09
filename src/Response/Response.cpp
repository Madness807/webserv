#include "../../include/Response/Response.hpp"

// Méthodes
// GETTERS
// SETTERS


// Constructeur
Response::Response(std::string &str): _request(str), _statusCode(200), _statusMessages(setStatusMessages()), _statusMessage(""), _headers(_request.getHeaders())
{
    if (_request.getRet() != 200)
        this->setStatusCode(_request.getRet());
    // else if (_server.getRet() != 200)
    //     this->setStatusCode(_server.getRet());
    else
        this->setStatusCode(200);
        std::cout << _request.getRaw() << std::endl;
    std::cout << _request << std::endl;
    setStatusLine();
    setHeaderLine();

}
// Destructeur
Response::~Response() {}

void    Response::setStatusCode(const int &code)
{
    _statusCode = code;
    _statusMessage = this->getStatusMessage(code);
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

std::string   Response::getContent() const
{
    return(_content);
}

std::string Response::getStatusMessage(const int &code)
{
    std::map<int, std::string>::iterator it = _statusMessages.find(code);
    if (it != _statusMessages.end())
        return (it->second);
    else
        return ("Error");
}

void    Response::setStatusLine()
{
    _content.append("HTTP/1.1 " + intToString(getStatusCode()) + " " + getStatusMessage(getStatusCode()) + "\r\n");
}

void Response::setHeaderLine()
{
    for (std::map<std::string, std::string>::const_iterator it = _request.getHeaders().begin(); it != _request.getHeaders().end(); ++it)
        if (it->second != "")
            _content.append(it->first + ":" + it->second + "\r\n");
    _content += "\r\n";
}

std::string Response::intToString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::ostream	&operator<<(std::ostream &out, const Response &response)
{
	out << "" << std::endl;
    out << COLOR_GREEN << " # REPONSE DES REQUETES HTTP" << COLOR_RESET << std::endl;
    out << "" << std::endl;
	out << response.getContent() << std::endl;

	return (out);
}



/*
Response.cpp
Rôle: Construit la réponse HTTP à envoyer au client.
Fonctions:
    Permet de construire une réponse HTTP, incluant le statut, les en-têtes, et le corps de la réponse.
    Offre des méthodes pour ajouter des en-têtes, définir le corps de la réponse, et éventuellement gérer les types de contenu MIME.
    Génère la réponse finale sous forme de chaîne ou de bytes à envoyer sur le réseau.
*/