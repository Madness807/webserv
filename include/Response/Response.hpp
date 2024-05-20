#ifndef RESPONSE_HPP
#define RESPONSE_HPP

 #include "../define.hpp"
 #include "../Request/Request.hpp"
 #include "../ConfigParser/ServerConfig.hpp"
 #include "../utils/utils.hpp"
 #include "../CGIHandler/CGIHandler.hpp"

class Response
{
    private:
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
        std::string                             _requestBody;
        bool                                    directoryListing;
        bool                                    _isCGI;
        std::string                             _cgiExtension;
        std::map<std::string, std::string>      mimeTypes;// Map des types MIME pour les content-type
        int                                     _bodysize;
    // SETTERS PRIVÉ
        void                                    setStatusCode(const int &code);
        std::map<int, std::string>              setStatusMessages();
        void                                    setStatusLine();
        void                                    setHeaders();
        void                                    setHeaderLine();
        void                                    setServer(ServerConfig &serverconfig);
        void                                    setContent();
        void                                    setErrorBody();
        void                                    setMethod();
        void                                    initMimeType();// Initialise la map des types MIME
        void                                    initResponseHeaders();// Initialise la map des méthodes
        void                                    setDirectoryListing(bool value);// Active ou désactive le listing des répertoires
        void                                    setCGI(bool value);// Active ou désactive le listing des répertoires
        void                                    setCGIExtension(const std::string &extension);// Active ou désactive le listing des répertoires

    // GETTERS PRIVÉ
        void                                    getHtmlFile(std::string path);
        std::string                             getPath();

    // METHODS PRIVÉE
        void                                    requestGet();
        void                                    requestPost();
        void                                    requestDelete();
        int                                     saveImage(const std::string &imageData, const std::string &boundary, const std::string& filename);
        int                                     addForm(std::string &filename);
        int                                     deleteResources(std::string &path);
        std::string						        findPathToDelete();

    public:

        // CONSTRUCTEUR / DESTRUCTEUR
        Response();
        Response(std::string &request, ServerConfig &serverConfig);
        ~Response();

        // GETTERS PUBLIC
        int                               getStatusCode() const;
        const std::string                 getStatusMessage(const int &code);
        const Request                     getRequest() const;
        const std::string                 getResponse() const;
        bool                              getDirectoryListing() const;
        bool                              getCGI() const;
        void                              getcgiExtension() const;

        // Methodes
        void                              generateDirectoryListing(const std::string& directoryPath, const std::string& path);
        void                              printHeaders() const;

};

std::string     intToString(int value);
std::ostream	&operator<<(std::ostream &out, const Response &response);

#endif
