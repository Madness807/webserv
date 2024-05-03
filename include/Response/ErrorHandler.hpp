#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include "../Response/Response.hpp"

class ErrorHandler {
public:
    ErrorHandler(Response& response);
    void handleError(int statusCode);

private:
    Response& _response;
};

#endif // ERRORHANDLER_HPP