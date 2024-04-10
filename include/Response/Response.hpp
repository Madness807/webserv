#ifndef RESPONSE_HPP
#define RESPONSE_HPP

 #include "../Request/Request.hpp"
 #include "../define.hpp"
 #include "../ConfigParser/ConfigParser.hpp"

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
        void                                    setStatusLine();
        void                                    setHeaders();
        void                                    setHeaderLine();

    public:
       
        Response(std::string &, ServerConfig &);
        ~Response();

    // Méthodes///////////////////
        // GETTERS
        int                                     getStatusCode() const;
        std::string                             getStatusMessage(const int &code);
        std::string                             getContent() const;
        Request                                 getRequest() const;

        std::string                             intToString(int value);
        // SETTERS
};

std::ostream	&operator<<(std::ostream &out, const Response &response);

#endif
