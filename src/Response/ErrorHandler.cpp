#include "ErrorHandler.hpp"

ErrorHandler::ErrorHandler(Response& response) : _response(response) {}

void ErrorHandler::handleError(int statusCode) {
    // Logique pour gérer les erreurs et générer des réponses d'erreur
}