#include "../../include/Response/Response.hpp"

//##################################################################
//                          Constructeur                           #
//##################################################################
Response::Response() {
	initMimeType();
}

Response::Response(const Request& request, ServerConfig& serverconfig): _request(request), _statusCode(_request.getRet()), _statusMessages(setStatusMessages()), _statusMessage(""), _body(""), _requestBody(_request.getBody(),)
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
void    Response::setStatusLine() //--> Creat status response
{
	_response.append("HTTP/1.1 " + intToString(getStatusCode()) + " " + getStatusMessage(getStatusCode()) + "\r\n");
}

void    Response::setHeaderLine() //--> Creat Header response
{
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it)
		if (!it->second.empty())
			_response.append(it->first + ":" + it->second + "\r\n");
	_response.append("\r\n");
}

void    Response::setContent() //--> Creat body response
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

void    Response::setErrorBody()
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

void    Response::setStatusCode(const int &code)
{
	_statusCode = code;
	_statusMessage = getStatusMessage(code);
}

void   Response::setMethod()
{
	_methods["GET"] = &Response::requestGet;
	_methods["POST"] = &Response::requestPost;
	_methods["DELETE"] = &Response::requestDelete;
}

std::map<int, std::string>    Response::setStatusMessages()
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

void    Response::setServer(ServerConfig &serverconfig)
{
	_server = serverconfig;
}

void    Response::setDirectoryListing(bool value)
{
	directoryListing = value;
}
//##################################################################
//                          Getter                                 #
//##################################################################
int Response::getStatusCode() const
{
	return (_statusCode);
}

const std::string   Response::getResponse() const
{
	return(_response);
}

const std::string Response::getStatusMessage(const int &code)
{
	std::map<int, std::string>::iterator it = _statusMessages.find(code);
	if (it != _statusMessages.end())
		return (it->second);
	else
		return ("Error");
}

const Request Response::getRequest() const
{
	return (_request);
}

bool Response::getDirectoryListing() const
{
	return (directoryListing);
}
//##################################################################
//                          Methods                                #
//##################################################################
void    Response::requestGet() // --> GET
{
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

void    Response::requestPost() // --> POST
{
	std::ofstream outFile;
	std::string postPath = "";

	std::cout << COLOR_GREEN << "REQUEST POST\t 🧑🏻‍💻 -> 🗄️\t  " << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << _request << std::endl;
	std::cout << COLOR_GREEN << "" << COLOR_RESET << std::endl;

	std::string dbPath = _server.getRoot() + _server.getLocationConfig("/submit-form").getRedirect();
	outFile.open(dbPath, std::ios::out | std::ios::app);
	
    if (outFile.is_open())
	{
		std::cout << "---------------> 1\n";
		outFile << _requestBody + "\n";
		setStatusCode(CREATED);
		outFile.close();
	}
	else
	{
		std::cout << "---------------> 2\n";
		setStatusCode(NOT_FOUND);
		setErrorBody();
		return;
	}
	postPath = "/";
	getHtmlFile(postPath);
}

void    Response::requestDelete() // --> DELETE
{
	std::cout << COLOR_GREEN << "REQUEST DELETE\t🖥️   ->   🗄️\t\t" << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	//std::cout << COLOR_GREEN << "│ " << COLOR_RESET << _request.getRaw() << std::endl;
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	std::cout << "" << std::endl;
}

void    Response::getHtmlFile(std::string path)
{
	std:: string root = _server.getRoot();
	std::string pathRedirection = _server.getRoot() + path;
	bool directoryListingState = getDirectoryListing();

	// CHECK IF THE PATH IS A DIRECTORY
    struct stat pathStat;
    if (stat(pathRedirection.c_str(), &pathStat) == 0 && S_ISDIR(pathStat.st_mode))
	{
        if (directoryListingState)
		{
            	generateDirectoryListing(pathRedirection, path);
            	return;
        } else 
		{
            	setStatusCode(FORBIDDEN);
            	setErrorBody();
            	return;
        }
   	}

	// CHECK IF THE PATH IS A CGI IS TRUE
	// lancer le cgi
	if (isCGI)
	{
		CGIHandler cgiHandler();// creer un objet cgiHandler

		cgiHandler.setPath(pathRedirection);// set le path du cgi

		cgiHandler.launchCGI();

		_headers["Content-Type"] = cgiHandler.getContentType();
		_headers["Content-Length"] = cgiHandler.getContentLength();
		_body = cgiHandler.getBody();


		// setStatusCode(OK);
		// setHeaders();
		// setHeaderLine();
		// setContent();
		// return;
	}


	// IS NOT A DIRECTORY
	// Get the file extension
	std::string extension = pathRedirection.substr(pathRedirection.find_last_of('.') + 1);
	std::map<std::string, std::string>::iterator mimeIterator = mimeTypes.find("." + extension);
	if (mimeIterator != mimeTypes.end())
	_headers["Content-Type"] = mimeIterator->second;

	// Open the file in binary mode and check if it's open
	std::ifstream inFile(pathRedirection.c_str(), std::ios::binary);
	if (!inFile.is_open())
	{
		setStatusCode(NOT_FOUND);
		setErrorBody();
		return;
	}
	// Lecture du fichier
	std::ostringstream ss;// Read the file
	ss << inFile.rdbuf(); // Read the whole file
	_body = ss.str();// Set the body to the file content
	inFile.close();// Close the file
	// Set the content length
	_headers["Content-Length"] = std::to_string(_body.size());
		
	return;
}

std::string Response::getPath()
{
	std::string path_from_request = "";
	std::string path_from_config = "";

	path_from_request = _request.getPath();
	bool isCGI = false;

	std::map<std::string, LocationConfig>::const_iterator it = _server.getMapLocation().find(_request.getPath()); // --> Check if path exist
	if (it != _server.getMapLocation().end())
	{
		if (it->second.getCgiPath().length() != 0 && it->second.getCgiExtension().length() != 0)
		{
			isCGI = true;
			path_from_config = it->second.getCgiPath();
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

//##################################################################
//                       INIT MIME TYPES                           #
//##################################################################
void Response::initMimeType()
{
	mimeTypes[".html"] = "text/html; charset=UTF-8";
	mimeTypes[".css"] = "text/css; charset=UTF-8";
	mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".jpeg"] = "image/jpeg";
	mimeTypes[".png"] = "image/png";
}

void Response::initResponseHeaders()
{
	_headers["Server"] = "MyCustomServer/1.0" ;
	_headers["Content-Type"] = "";
}

//##################################################################
//                          Others                                 #
//##################################################################
void Response::printHeaders() const
{// Print the headers
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		std::cout << it->first << ": " << it->second << "\n";
	}
	std::cout << std::endl;
}

std::string intToString(int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

std::ostream	&operator<<(std::ostream &out, const Response &response)
{
	out << "" << std::endl;
	out << COLOR_GREEN << " # REPONSE DES REQUETES HTTP" << COLOR_RESET << std::endl;
	out << "" << std::endl;
	out << response.getResponse() << std::endl;

	return (out);
}

void Response::generateDirectoryListing(const std::string& directoryPath, const std::string& path) {
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


