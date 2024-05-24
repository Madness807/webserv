#include "../../include/Response/Response.hpp"

//##################################################################
//                          Constructeur                           #
//##################################################################
Response::Response()
{
	initMimeType();
}

Response::Response(std::string &request, ServerConfig& serverConfig): _request(request, serverConfig), _statusCode(_request.getRet()), _statusMessages(setStatusMessages()), _statusMessage(""), _body(""), _requestBody(_request.getBody())
{
	initMimeType();// Initialize the MIME types
	setServer(serverConfig);// Set the server
	setMethod();// Set the methods
	setContent();// Set the content of the response
	setStatusLine();// Set the status of the response
	setHeaderLine();// Set the header of the response
	_isCGI = false;
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

void							Response::setContent()							//--> Creat body response
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

void							Response::setErrorBody()						//--> Creat body error response
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

void							Response::setStatusCode(const int &code)		//--> Creat status code response
{
	_statusCode = code;
	_statusMessage = getStatusMessage(code);
}

void							Response::setMethod()							//--> Set the methods
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

void							Response::setServer(ServerConfig &serverconfig)	//--> Set the server
{
	_server = serverconfig;
}

void							Response::setDirectoryListing(bool value)		//--> Set the directory listing
{
	directoryListing = value;
}

//##################################################################
//                          Getter                                 #
//##################################################################

int								Response::getStatusCode() const					//--> Get the status code
{
	return (_statusCode);
}

const std::string				Response::getResponse() const					//--> Get the response
{
	return(_response);
}

const std::string				Response::getStatusMessage(const int &code)		//--> Get the status message
{
	std::map<int, std::string>::iterator it = _statusMessages.find(code);
	if (it != _statusMessages.end())
		return (it->second);
	else
		return ("Error");
}

const Request					Response::getRequest() const					//--> Get the request
{
	return (_request);
}

bool							Response::getDirectoryListing() const			//--> Get the directory listing
{
	return (directoryListing);
}


//##################################################################
//                          Methods                                #
//##################################################################

void							Response::getHtmlFile(std::string path)			// construction de la reponse
{
	std::string root = 				_server.getRoot();
	std::string pathRedirection = 	_server.getRoot() + path;
	bool directoryListingState = 	getDirectoryListing();

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

	// CHECK IF THE PATH IS A CGI
	if (this->_isCGI)
	{
		int ret = 0;
		CGIHandler cgiHandler(pathRedirection);// creer un objet cgiHandler
		if (_cgiExtension == ".py")
		{
			ret = cgiHandler.execute();// execute le cgi
			if (ret == 500)
			{
				setStatusCode(500);
				return;
			}
			_headers["Content-Type"] = cgiHandler.getCgiContentType();
			_headers["Content-Length"] = std::to_string(cgiHandler.getBody().size());
			_body = cgiHandler.getBody();
			return;
		}
		else
		{
			perror("ERROR: CGI bad extension");
			setStatusCode(500);
			return;
		}
	}

	// Check if the path is a file
	// Get the file extension
	std::string extension = pathRedirection.substr(pathRedirection.find_last_of('.') + 1);
	std::map<std::string, std::string>::iterator mimeIterator = mimeTypes.find("." + extension);
	if (mimeIterator != mimeTypes.end())
	_headers["Content-Type"] = mimeIterator->second;

	// Open the file in binary mode and check if it's open
	std::ifstream inFile(pathRedirection.c_str(), std::ios::binary);
	if (!inFile.is_open())
	{
		int err = errno;
		if (err == ENOENT)
		{
            std::cerr << "Erreur: Le fichier n'existe pas." << std::endl;
			setStatusCode(NOT_FOUND);
        }
		else if (err == EACCES)
		{
            std::cerr << "Erreur: Permission refusée." << std::endl;
			setStatusCode(FORBIDDEN);
        }
		else
		{
            std::cerr << "Erreur: " << std::strerror(err) << std::endl;
			setStatusCode(NOT_FOUND);
        }
		setErrorBody();
		return;
	}
	// Lecture du fichier
	std::ostringstream ss;// Read the file
	ss << inFile.rdbuf(); // Read the whole file
	_body = ss.str();// Set the body to the file content
	inFile.close();// Close the file

	_headers["Content-Length"] = std::to_string(_body.size());

	return;
}

std::string						Response::getPath()								// --> Get the path of ..
{
	std::string path_from_request = "";
	std::string path_from_config = "";

	path_from_request = _request.getPath();

	std::map<std::string, LocationConfig>::const_iterator it = _server.getMapLocation().find(_request.getPath()); // --> Check if path exist
	if (it != _server.getMapLocation().end())
	{
		if (it->second.getCgiPath().length() != 0 && it->second.getCgiExtension().length() != 0)
		{
			this->_isCGI = true;
			path_from_request = it->second.getCgiPath();
			_cgiExtension = it->second.getCgiExtension();
		}

		std::vector<std::string> methods = it->second.getMethods();
	    std::string requestMethod = _request.getMethod();
		std::vector<std::string>::iterator it2 = std::find(methods.begin(), methods.end(), requestMethod);
        if (it2 == methods.end())
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

int 							Response::saveImage(const std::string &imageData, const std::string &boundary, const std::string &filename)	//--> Save Upload Image Data
{
	static int nb;
	size_t startPos = imageData.find("Content-Type: image/png");
    if (startPos != std::string::npos)
	{
        startPos = imageData.find("\r\n\r\n", startPos) + 4; // Sauter l'en-tête jusqu'au début des données
        size_t endPos = imageData.find(boundary, startPos) - 2; // -2 pour enlever le \r\n avant la limite

        if (startPos != std::string::npos && endPos != std::string::npos)
		{
			std::string outFile = filename + "image_" + intToString(nb++) + ".png";
            std::ofstream file(outFile, std::ios::out | std::ios::app | std::ios::binary);
			// std::cout << file.is_open() << " & " << outFile << std::endl;
            if (!file.is_open())
			{
                std::cerr << COLOR_RED << "Erreur lors de l'ouverture du fichier pour écriture." << COLOR_RESET << std::endl;
                return (1);
            }

			// std::cout << "Binary Data: " << imageData.data() + startPos << std::endl;
            file.write(imageData.data() + startPos,  endPos - startPos);
			setStatusCode(CREATED);
            file.close();
        } else
            std::cerr << COLOR_RED <<  "Limites des données d'image non trouvées." << COLOR_RESET << std::endl;
    }
	else
        std::cerr << COLOR_RED << "En-tête Content-Type non trouvé." << COLOR_RESET << std::endl;
	return (0);
}

int								Response::addForm(std::string &filename) 		//--> Add info formulaire
{
	std::ofstream outFile (filename.c_str(), std::ios::app | std::ios::out);
	if (!outFile.is_open())
	{
        std::cerr << COLOR_RED << "Erreur lors de l'ouverture du fichier -> Form." << COLOR_RESET << std::endl;
        return (1);
    }

	outFile << _requestBody + "\n";
	setStatusCode(CREATED);
	outFile.close();
	return (0);
}

std::string						Response::findPathToDelete()
{
	 size_t startPos = _requestBody.find("\"path\":\"");
    if (startPos == std::string::npos)
        return ""; // La clé "path" n'a pas été trouvée
    startPos += 8; // Pour dépasser le préfixe "\"path\":\""
    size_t endPos = _requestBody.find("\"", startPos);
    if (endPos == std::string::npos)
        return ""; // La fin de la valeur n'a pas été trouvée
    return (_requestBody.substr(startPos, endPos - startPos));
}

//##################################################################
//                       HTTP REQUEST                              #
//##################################################################

void							Response::requestGet()							// http request GET
{
	std::cout << COLOR_GREEN << "REQUEST GET\t🖥️   ->   🗄️\t\t" << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN << "│ " << COLOR_RESET << _request.getRaw() << std::endl;
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	std::cout << _request << std::endl;
	std::cout << "" << std::endl;

	if (_server.getErrorCode() != 200)
		setStatusCode(_server.getErrorCode());

	if (getStatusCode() != 200)
		setErrorBody();
	else
		getHtmlFile(getPath());
}

void							Response::requestPost()							// http request POST
{
	std::string dbPath = getPath();
	std::stringstream bodysizeStr(_server.getMaxBodySize());
	std::cout << COLOR_GREEN << "REQUEST POST\t 🧑🏻‍💻 -> 🗄️\t  " << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << _request << std::endl;
	std::cout << COLOR_GREEN << "" << COLOR_RESET << std::endl;

	if (_request.getBodySize() > ft_atoi(_server.getMaxBodySize())) // Check bodySize
		setStatusCode(413);
	else if (!_request.getOneHeaders("Content-Type").find("application/x-www-form-urlencoded"))
	{
		dbPath = _server.getRoot() + "/db/forumlaire.txt";
		if (addForm(dbPath))
			setStatusCode(INTERNAL_SERVER_ERROR);
	}
	else if (!_request.getOneHeaders("Content-Type").find("multipart/form-data"))
	{
		dbPath = _server.getRoot() + "/upload/";
		if (saveImage(_requestBody, _request.getBoundary(), dbPath))
			setStatusCode(INTERNAL_SERVER_ERROR);
	}

	if (_server.getErrorCode() != 200)
		setStatusCode(_server.getErrorCode());

	if (getStatusCode() >= 400 && 500 >= getStatusCode())
	{
		setErrorBody();
		return;
	}
	if (!_isCGI)
		getHtmlFile("/index.html");
}

void							Response::requestDelete()						// http request DELETE
{
	std::cout << COLOR_GREEN << "REQUEST DELETE\t🖥️   ->   🗄️\t\t" << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN << "│ " << COLOR_RESET << _request << std::endl;
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	std::cout << "" << std::endl;

	std::string deletePath(_server.getRoot() + _request.getPath() + findPathToDelete());
	if (deletePath.find("..") == 0)
	{
		setStatusCode(403);
		setErrorBody();
		return;
	}
	if (pathIsFile(deletePath))
	{
		if (hasWritePermission(deletePath))
		{
			if (deletePath.find(_server.getRoot() + "/delete_item/") == 0)
			{
				if (remove(deletePath.c_str()) == 0)
					setStatusCode(204); // No Content
				else
					setStatusCode(403); // Forbidden, erreur lors de la suppression
			}
		}
		else
			setStatusCode(403); // Forbidden, pas de permission d'écriture
	}
	else
		setStatusCode(404); // Not Found

	if (_server.getErrorCode() != 200) // Check if Error on server
		setStatusCode(_server.getErrorCode());

	if (getStatusCode() >= 400 || getStatusCode() <= 500)
	{
		setErrorBody();
		return;
	}
	getHtmlFile("/index.html");
}

//##################################################################
//                           INIT                                  #
//##################################################################

void							Response::initMimeType()						//--> Initialize the MIME types
{
	mimeTypes[".html"] = "text/html; charset=UTF-8";
	mimeTypes[".css"] = "text/css; charset=UTF-8";
	mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".jpeg"] = "image/jpeg";
	mimeTypes[".png"] = "image/png";
}

void 							Response::initResponseHeaders()					//--> Initialize the response headers
{
	_headers["Server"] = "MyCustomServer/1.0" ;
	_headers["Content-Type"] = "";
}

//##################################################################
//                          Others                                 #
//##################################################################

void							Response::printHeaders() const					//--> Print the headers
{
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		std::cout << it->first << ": " << it->second << "\n";
	}
	std::cout << std::endl;
}

std::string						intToString(int value)							//--> Convert int to string
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

std::ostream					&operator<<(std::ostream &out, const Response &response)	// --> Overload the << operator
{
	out << "" << std::endl;
	out << COLOR_GREEN << " # REPONSE DES REQUETES HTTP" << COLOR_RESET << std::endl;
	out << "" << std::endl;
	out << response.getResponse() << std::endl;

	return (out);
}

void							Response::generateDirectoryListing(const std::string& directoryPath, const std::string& path)	//--> Generate the directory listing
{
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
