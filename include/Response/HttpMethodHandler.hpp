#ifndef HTTPMETHODHANDLER_HPP
#define HTTPMETHODHANDLER_HPP

#include "../Request/Request.hpp"
#include "../Response/Response.hpp"

class HttpMethodHandler
{
    public:
        HttpMethodHandler(const Request& request, Response& response);
        void handleRequest();

    private:
        //methods
        void handleGet();
        void handlePost();
        void handleDelete();
    
    const Request& _request;
    Response& _response;
};

#endif // HTTPMETHODHANDLER_HPP