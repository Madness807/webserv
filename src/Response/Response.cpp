#include "../../include/Response/Response.hpp"

//##################################################################
//                          Constructeur                           #
//##################################################################
Response::Response() {
	initMimeType();
}

Response::Response(const Request& request, ServerConfig& serverconfig): _request(request), _statusCode(_request.getRet()), _statusMessages(setStatusMessages()), _statusMessage(""), _body(""), _requestBody(_request.getBody())
{   
	initMimeType();// Initialize the MIME types
	setServer(serverconfig);// Set the server
	setMethod();// Set the methods
	setContent();// Set the content of the response
	setStatusLine();// Set the status of the response
	setHeaderLine();// Set the header of the response
}

//##################################################################
//                          Destructeur                            #
//##################################################################
Response::~Response() {}

//##################################################################
//                          Setter                                 #
//##################################################################
void							Response::setStatusLine()						//--> Creat status response
{
	_response.append("HTTP/1.1 " + intToString(getStatusCode()) + " " + getStatusMessage(getStatusCode()) + "\r\n");
}

void							Response::setHeaderLine()						//--> Creat Header response
{
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it)
		if (!it->second.empty())
			_response.append(it->first + ":" + it->second + "\r\n");
	_response.append("\r\n");
}

void							Response::setContent()							//--> construction de tout le contenu de la reponse
{
	if (getStatusCode() != 200)
		setErrorBody();
	else
	{
		std::map<std::string, ptrFt>::iterator it = _methods.find(_request.getMethod());
		if (it != _methods.end())
		{
			ptrFt method = it->second;
			(this->*method)();
		}
		else
		{
			setStatusCode(405);
			setErrorBody();
		}
	}
	setStatusLine();
	setHeaderLine();
	_response.append(_body);

	std::cout << COLOR_GREEN << "REPONSE REQUEST\t🗄️   ->   🖥️\t\t" << getCurrentTimestamp() << COLOR_RESET << std::endl;
	 std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	 //std::cout << _response <<  std::endl;
	 std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
}

void							Response::setErrorBody()						// --> Error body
{
	std::string errorPath = _server.getErrorPage().substr(0, _server.getErrorPage().find_last_of("/") + 1);
	std::string errPath = _server.getRoot() + errorPath + intToString(getStatusCode()) + ".html";
	const char* filename = errPath.c_str();
	std::ifstream inFile(filename, std::ifstream::in);
	if (!inFile.is_open())
		perror("open");
	std::string line;
	while (std::getline(inFile, line))
	{
		if (_body != "")
		{
			_body.append(line);
			continue;
		}
		_body = line;
	}
	inFile.close();
}

void							Response::setStatusCode(const int &code)		// --> Set status code
{
	_statusCode = code;
	_statusMessage = getStatusMessage(code);
}

void							Response::setMethod()							// --> Set the methods
{
	_methods["GET"] = &Response::requestGet;
	_methods["POST"] = &Response::requestPost;
	_methods["DELETE"] = &Response::requestDelete;
}

std::map<int, std::string>		Response::setStatusMessages()					//--> Set the status messages
{
	std::map<int, std::string>  messages;
	messages[200] = "OK";
	messages[201] = "Created";
	messages[202] = "Accepted";
	messages[204] = "No Content";
	messages[301] = "Move Permanently";
	messages[302] = "Found";
	messages[304] = "Not Modified";
	messages[400] = "Bad Request";
	messages[401] = "Unauthorized";
	messages[403] = "Forbidden";
	messages[404] = "Not Found";
	messages[405] = "Method Not Allowed";
	messages[500] = "Internal Server Error";
	messages[501] = "Not Implemented";
	messages[502] = "Bad Gateway";
	messages[503] = "Service Unvailable";
	return (messages);
}

void    						Response::setServer(ServerConfig &serverconfig)	// --> Set the server
{
	_server = serverconfig;
}

void    						Response::setDirectoryListing(bool value)		// --> Set the directory listing
{
	directoryListing = value;
}

//##################################################################
//                          Getter                                 #
//##################################################################
int								Response::getStatusCode() const
{
	return (_statusCode);
}

const std::string				Response::getResponse() const
{
	return(_response);
}

const std::string				Response::getStatusMessage(const int &code)
{
	std::map<int, std::string>::iterator it = _statusMessages.find(code);
	if (it != _statusMessages.end())
		return (it->second);
	else
		return ("Error");
}

const Request 					Response::getRequest() const
{
	return (_request);
}

bool							Response::getDirectoryListing() const
{
	return (directoryListing);
}
//##################################################################
//                          Methods                                #
//##################################################################

void							Response::getHtmlFile(std::string path)
{
	std::string root = 				_server.getRoot();
	std::string pathRedirection = 	_server.getRoot() + path;
	bool directoryListingState = 	getDirectoryListing();
	isCGI = false;

	// CHECK IF THE PATH IS A DIRECTORY
	struct stat pathStat;
	if (stat(pathRedirection.c_str(), &pathStat) == 0 && S_ISDIR(pathStat.st_mode))
	{
		handleDirectory(path, pathRedirection, directoryListingState);
		return;
   	}

	// CHECK IF THE PATH IS A CGI
	if (isCGI) {
		handleCGI(pathRedirection);
		return;
	}

	// CHECK IF THE PATH IS A FILE
    readAndSetFileContent(pathRedirection);

	return;
}

std::string						Response::getPath()
{
	std::string path_from_request = "";
	std::string path_from_config = "";

	path_from_request = _request.getPath();
	//bool isCGI = false;

	std::map<std::string, LocationConfig>::const_iterator it = _server.getMapLocation().find(_request.getPath()); // --> Check if path exist
	if (it != _server.getMapLocation().end())
	{
		if (it->second.getCgiPath().length() != 0 && it->second.getCgiExtension().length() != 0)
		{
			isCGI = true;
			path_from_request = it->second.getCgiPath();
			_cgiExtension = it->second.getCgiExtension();
		}

		std::vector<std::string>::iterator it2 = std::find(it->second.getMethods().begin(), it->second.getMethods().end(), _request.getMethod()); // --> Check if Method allowed for this path
		if (it2 == it->second.getMethods().end())
		{
			setStatusCode(METHOD_NOT_ALLOWED);
			setErrorBody();
			return ("");
		}
		path_from_config = it->second.getRedirect(); // tester dans le cas ou cest un path qui provient du fichier de config
		setDirectoryListing(it->second.getDirectoryListing());
	}
	else {
		setDirectoryListing(true);
	}
	if (path_from_config != "")
		return(path_from_config);
	else
		return(path_from_request);
}

void							Response::initResponseHeaders()
{
	_headers["Server"] = "MyCustomServer/1.0" ;
	_headers["Content-Type"] = "";
}

void							Response::handleDirectory(const std::string& path, const std::string& pathRedirection, bool directoryListingState) {
    if (directoryListingState) {
        generateDirectoryListing(pathRedirection, path);
    } else {
        setStatusCode(FORBIDDEN);
        setErrorBody();
    }
}

void							Response::handleCGI(const std::string& pathRedirection) {
    int success = 0;
    CGIHandler cgiHandler(pathRedirection);

    if (_cgiExtension == ".py") {
        success = cgiHandler.execute();
        if (success == 500) {
            setStatusCode(500);
            return;
        }
        _headers["Content-Type"] = cgiHandler.getCgiContentType();
        _headers["Content-Length"] = std::to_string(cgiHandler.getBody().size());
        _body = cgiHandler.getBody();
    } else {
        perror("ERROR: CGI bad extension");
        setStatusCode(500);
    }
}

void							Response::readAndSetFileContent(const std::string& pathRedirection) {
    std::string extension = pathRedirection.substr(pathRedirection.find_last_of('.') + 1);
    std::map<std::string, std::string>::iterator mimeIterator = mimeTypes.find("." + extension);
    if (mimeIterator != mimeTypes.end())
        _headers["Content-Type"] = mimeIterator->second;

    std::ifstream inFile(pathRedirection.c_str(), std::ios::binary);
    if (!inFile.is_open())
    {
        setStatusCode(NOT_FOUND);
        setErrorBody();
        return;
    }

    std::ostringstream ss;
    ss << inFile.rdbuf();
    _body = ss.str();
    inFile.close();

    _headers["Content-Length"] = std::to_string(_body.size());
}

//##################################################################
//                          Others                                 #
//##################################################################
void							Response::printHeaders() const
{
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		std::cout << it->first << ": " << it->second << "\n";
	}
	std::cout << std::endl;
}

std::ostream	&operator<<(std::ostream &out, const Response &response)
{
	out << "" << std::endl;
	out << COLOR_GREEN << " # REPONSE DES REQUETES HTTP" << COLOR_RESET << std::endl;
	out << "" << std::endl;
	out << response.getResponse() << std::endl;

	return (out);
}

void 							Response::generateDirectoryListing(const std::string& directoryPath, const std::string& path) {
	std::ostringstream html;
	html << "<html><body><h1>Directory Listing of " << directoryPath << "</h1><ul>";

	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir(directoryPath.c_str())) != NULL) {
		while ((entry = readdir(dir)) != NULL) {
			std::string hrefPath = path + "/" +entry->d_name;
			if (entry->d_type == DT_DIR) {
				// Pour les répertoires, ajoutez un slash à la fin du nom
				html << "<li><a href=\"" << hrefPath << "/\">" << entry->d_name << "/</a></li>";
			} else {
				html << "<li><a href=\"" << hrefPath << "\">" << entry->d_name << "</a></li>";
			}
		}
		closedir(dir);
	} else {
		setStatusCode(INTERNAL_SERVER_ERROR);
		setErrorBody();
		return;
	}

	html << "</ul></body></html>";
	_body = html.str();
	_headers["Content-Type"] = "text/html";
	_headers["Content-Length"] = std::to_string(_body.size());
}
