#ifndef RESPONSE_HPP
#define RESPONSE_HPP

 #include "../Request/Request.hpp"
 #include "../define.hpp"
 #include "../ConfigParser/ServerConfig.hpp"

class Response 
{
        Request                                 _request;
        ServerConfig                            _server;
        int                                     _statusCode;
        std::map<int , std::string>             _statusMessages;
        std::string                             _statusMessage;
        typedef void                            (Response::*ptrFt)(void);
        std::map<std::string, ptrFt>            _methods;
        std::map<std::string , std::string>     _headers;
        std::string                             _response;
        std::string                             _body;

    // SETTERS
        void                                    setStatusCode(const int &code);
        std::map<int, std::string>              setStatusMessages();
        void                                    setStatusLine();
        void                                    setHeaders();
        void                                    setHeaderLine();
        void                                    setServer(ServerConfig &serverconfig);
        void                                    setContent();
        void                                    setErrorBody();
        void                                    setMethod();
        void                                    getMethod();
        void                                    postMethod();
        void                                    deleteMethod();

    public:
       
        Response();
        Response(std::string &, ServerConfig &);
        ~Response();

    // Méthodes///////////////////
        // GETTERS
        int                               getStatusCode() const;
        const std::string                 getStatusMessage(const int &code);
        const Request                     getRequest() const;
        const std::string                 getResponse() const;

};

std::string     intToString(int value);
std::ostream	&operator<<(std::ostream &out, const Response &response);

#endif
