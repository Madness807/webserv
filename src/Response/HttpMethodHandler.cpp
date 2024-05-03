#include "HttpMethodHandler.hpp"

HttpMethodHandler::HttpMethodHandler(const Request& request, Response& response)
    : _request(request), _response(response) {}

void HttpMethodHandler::handleRequest() {
    if (_request.getMethod() == "GET") {
        handleGet();
    } else if (_request.getMethod() == "POST") {
        handlePost();
    } else if (_request.getMethod() == "DELETE") {
        handleDelete();
    }
}

//##################################################################
//                             GET                                 #
//##################################################################

void HttpMethodHandler::handleGet() {

	std::string getResponse = "";

	std::cout << COLOR_GREEN << "REQUEST GET\t🖥️   ->   🗄️\t\t" << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN << "│ " << COLOR_RESET << _request.getRaw() << std::endl;
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	std::cout << "" << std::endl;

	getResponse = getPath();
	if (getStatusCode() != METHOD_NOT_ALLOWED)
		getHtmlFile(getPath());
}


//##################################################################
//                             POST                                #
//##################################################################

void HttpMethodHandler::handlePost() {

	std::string postPath = "";
	std::stringstream bodysizeStr(_server.getMaxBodySize());
	std::cout << COLOR_GREEN << "REQUEST POST\t 🧑🏻‍💻 -> 🗄️\t  " << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << _request << std::endl;
	std::cout << COLOR_GREEN << "" << COLOR_RESET << std::endl;

	// bodysizeStr >> _bodysize;
	// std::cout << "BODYSIZE : " <<_bodysize << std::endl;
	// if (_bodysize < _requestBody.size())
	// {
	// 	setStatusCode(413);
	// 	setErrorBody();
	// 	return;
	// } PAS SUR QUE CELA MARCHE POUR LE MOMENT

	//std::string dbPath = _server.getRoot() + "/db/forumlaire.txt"; //TEST AVEC UN FICHIER TXT
	std::string dbPath = _server.getRoot() + "/upload/image.jpeg"; //TEST AVEC IMAGE

	//outFile.open(dbPath, std::ios::out | std::ios::app | std::ios::binary);// Open the file in binary mode
	std::ofstream outFile(dbPath, std::ios::out | std::ios::app | std::ios::binary);// Open the file in binary mode
	
	if (outFile.is_open())// Check if the file is open
	{
		std::cout << COLOR_GREEN << "l ouverture du fichier a reussi" << COLOR_RESET << std::endl;
		outFile.write(_requestBody.c_str(), _requestBody.size());

		//outFile << _requestBody + "\n";
		setStatusCode(CREATED);
		outFile.close();
	}
	else// If the file is not open
	{
		std::cout << COLOR_RED <<"l ouverture du fichier a echoue" << COLOR_RESET << std::endl;
		setStatusCode(NOT_FOUND);
		setErrorBody();
		return;
	}

	// Reponse de la requete au client
	getHtmlFile("/page/index.html");
}


//##################################################################
//                             DELETE                              #
//##################################################################

void HttpMethodHandler::handleDelete() {

	std::cout << COLOR_GREEN << "REQUEST DELETE\t🖥️   ->   🗄️\t\t" << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	//std::cout << COLOR_GREEN << "│ " << COLOR_RESET << _request.getRaw() << std::endl;
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	std::cout << "" << std::endl;
}
