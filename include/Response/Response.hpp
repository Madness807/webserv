#ifndef RESPONSE_HPP
#define RESPONSE_HPP

 #include "../Request/Request.hpp"
 #include "../define.hpp"

class Response 
{
        Request                                 _request;
        // ServerConfig                            _server;
        int                                     _statusCode;
        std::map<int , std::string>             _statusMessages;
        std::string                             _statusMessage;
        std::string                             _content;
        std::map<std::string , std::string>     _headers;

        void                                    setStatusCode(const int &code);
        std::map<int, std::string>              setStatusMessages();

    public:
       
        Response(std::string &str);
        ~Response();

    // Méthodes///////////////////
        // GETTERS
        int                                     getStatusCode() const;
        std::string                             getStatusMessage(const int &code);
        std::string                             getContent() const;
        // SETTERS
};

#endif
