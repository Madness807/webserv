#ifndef RESPONSE_HPP
#define RESPONSE_HPP

 #include "../Request/Request.hpp"
 #include "../define.hpp"
 #include "../ConfigParser/ConfigParser.hpp"

class Response
{
        Request                                 _request;
        ServerConfig                            _server;
        int                                     _statusCode;
        std::map<int , std::string>             _statusMessages;
        std::string                             _statusMessage;
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

    public:

        Response(std::string &, ServerConfig &);
        ~Response();

    // Méthodes///////////////////
        void                                    getMethod();
        void                                    postMethod();
        void                                    deleteMethod();
        // GETTERS
        int                                     getStatusCode() const;
        std::string                             getStatusMessage(const int &code);
        Request                                 getRequest() const;
        std::string                             getResponse() const;

};

std::string     intToString(int value);
std::ostream	&operator<<(std::ostream &out, const Response &response);

#endif
