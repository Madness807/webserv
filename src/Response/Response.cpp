#include "../../include/Response/Response.hpp"

// Constructeur
//Response::Response() : _request() {}
// Response::Response(std::string &str, ServerConfig &serverconfig): _request(str), _statusCode(_request.getRet()), _statusMessages(setStatusMessages()), _statusMessage(""), _methods(setMethod()), _headers(_request.getHeaders()), _body("")

Response::Response(std::string &str, ServerConfig &serverconfig): _request(str), _statusCode(_request.getRet()), _statusMessages(setStatusMessages()), _statusMessage(""), _headers(_request.getHeaders()), _body("")
{
    this->setServer(serverconfig);
    // if (_server.getRet() != 200)
    //     this->setStatusCode(_server.getRet());

        this->setStatusCode(200);
    // if(_request.getEnv() != "") --> If CGI exist
    // if (server.getCgi() == "On") -->> si cgi actif
        // go->cgi();
    this->setStatusLine();
    this->setHeaderLine();
    this->setContent();
    std::cout << _request << std::endl;
}

// Destructeur
Response::~Response() {}

//Setter
void    Response::setStatusLine()
{
    _response.append("HTTP/1.1 " + intToString(getStatusCode()) + " " + getStatusMessage(getStatusCode()) + "\r\n");
}

void Response::setHeaderLine()
{
    for (std::map<std::string, std::string>::const_iterator it = _request.getHeaders().begin(); it != _request.getHeaders().end(); ++it)
        if (it->second != "")
            _response.append(it->first + ":" + it->second + "\r\n");
    _response.append("\r\n");
}

void    Response::setContent()
{
    // if (_request.getMethod() == "GET")
    //     this->getMethod();
    // else if (_request.getMethod() == "POST")
    //     this->postMethod();
    // else if (_request.getMethod() == "DELETE")
    //     this->deleteMethod();
    // else
    // {
        this->setStatusCode(405);
        this->setErrorBody();
    // }
    _response.append(_body);
}

void    Response::setErrorBody()
{
    std::string errPath = "website/errors/" + intToString(this->getStatusCode()) + ".html";
    std::cout << errPath << std::endl;
    const char* filename = errPath.c_str();
    std::ifstream inFile(filename, std::ifstream::in);
    if (!inFile.is_open())
        perror("open");
    std::string line;
    while (std::getline(inFile, line))
    {
        if (this->_body != "")
        {
            this->_body.append(line);
            continue;
        }
        this->_body = line;
    }
    inFile.close();
}

// int main() {
//     std::string errPath = "your_error_file.txt"; // Replace with your actual error file path
//     // Convert std::string to const char*

//     std::ifstream inFile(filename); // Open the file

//     if (!inFile.is_open()) {
//         std::cerr << "Error opening file: " << errPath << std::endl;
//         return 1;
//     }

//     // Rest of your code here

//     inFile.close();
//     return 0;
// }

void    Response::setStatusCode(const int &code)
{
    _statusCode = code;
    _statusMessage = this->getStatusMessage(code);
}

void   Response::setMethod()
{
    _methods["GET"] = &Response::getMethod;
    _methods["POST"] = &Response::postMethod;
    _methods["DELETE"] = &Response::deleteMethod;
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

void    Response::setServer(ServerConfig &serverconfig)
{
    _server = serverconfig;
}


// Getter
const int Response::getStatusCode() const
{
    return (_statusCode);
}

const std::string   Response::getResponse() const
{
    return(_response);
}

const std::string Response::getStatusMessage(const int &code)
{
    std::map<int, std::string>::iterator it = _statusMessages.find(code);
    if (it != _statusMessages.end())
        return (it->second);
    else
        return ("Error");
}

const Request Response::getRequest() const
{
    return (_request);
}


//Other
std::string intToString(int value)
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
	out << response.getResponse() << std::endl;

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
