#include "../../include/Response/Response.hpp"

//##################################################################
//                          Constructeur                           #
//##################################################################
Response::Response()
{
	initMimeType();
}

Response::Response(std::string &request, ServerConfig &serverConfig): _request(request, serverConfig), _statusCode(_request.getRet()), _statusMessages(setStatusMessages()), _statusMessage(""), _body(""), _requestBody(_request.getBody())
{   
	// std::cout << COLOR_GREEN << request << COLOR_RESET << std::endl << std::endl;
	// std::cout << request << std::endl;
	initMimeType();// Initialize the MIME types
	setServer(serverConfig);// Set the server
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

int 							Response::saveImage(const std::string &imageData, const std::string &boundary, const std::string &filename)	//--> Save Upload Image Data
{
	std::cout << "je suis au 3.1" << std::endl;

	static int nb;
	size_t startPos = imageData.find("Content-Type: image/png");
    if (startPos != std::string::npos)
	{
		std::cout << "je suis au 3.2" << std::endl;

        startPos = imageData.find("\r\n\r\n", startPos) + 4; // Sauter l'en-tête jusqu'au début des données
        size_t endPos = imageData.find(boundary, startPos) - 2; // -2 pour enlever le \r\n avant la limite

        if (startPos != std::string::npos && endPos != std::string::npos)
		{
			std::cout << "je suis au 3.3" << std::endl;

			std::string outFile = filename + "image_" + intToString(nb++) + ".png";
            std::ofstream file(outFile, std::ios::out | std::ios::app | std::ios::binary);
			// std::cout << file.is_open() << " & " << outFile << std::endl;
            if (!file.is_open())
			{
                std::cerr << COLOR_RED << "Erreur lors de l'ouverture du fichier pour écriture." << COLOR_RESET << std::endl;
                return (1);
            }

			// std::cout << "Binary Data: " << imageData.data() + startPos << std::endl;
            file.write(imageData.data() + startPos,  std::string::npos);
			setStatusCode(CREATED);
            file.close();
        } else
            std::cerr << COLOR_RED <<  "Limites des données d'image non trouvées." << COLOR_RESET << std::endl;
    }
	else
        std::cerr << COLOR_RED << "En-tête Content-Type non trouvé." << COLOR_RESET << std::endl;
	// static int nb;
	// std::string file = filename + "image_" + intToString(nb++) + ".png";
    // std::ofstream outFile(file.c_str(), std::ios::out | std::ios::binary);
    // if (!outFile.is_open())
	// {
    //     std::cerr << "Erreur lors de l'ouverture du fichier -> Image." << std::endl;
    //     return (0);
    // }
	// size_t startPos = imageData.find("\r\n\r\n")
    // outFile.write(imageData, size);
	// setStatusCode(CREATED);
    // outFile.close();
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

int								Response::deleteResources(std::string &path)
{
	if (std::remove(path.c_str()))
		return (1);
	return (0);
}

//##################################################################
//                          Methods                                #
//##################################################################

void							Response::getHtmlFile(std::string path)			// construction de la reponse
{
	std::string root = 				_server.getRoot();
	std::string pathRedirection = 	_server.getRoot() + path;
	bool directoryListingState = 	getDirectoryListing();
	isCGI = false;

	std::cout << "je suis au 4" << std::endl;

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
	if (isCGI)
	{
		int success = 0;
		CGIHandler cgiHandler(pathRedirection);// creer un objet cgiHandler

		if (_cgiExtension == ".py")
		{
			success = cgiHandler.execute();// execute le cgi
			if (success == 500)
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
		setStatusCode(NOT_FOUND);
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

//##################################################################
//                       HTTP REQUEST                              #
//##################################################################

void							Response::requestGet()							// http request GET
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

void							Response::requestPost()							// http request POST
{
	//std::ofstream outFile;
	std::string dbPath = getPath();
	std::stringstream bodysizeStr(_server.getMaxBodySize());
	std::cout << COLOR_GREEN << "REQUEST POST\t 🧑🏻‍💻 -> 🗄️\t  " << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << _request << std::endl;
	std::cout << COLOR_GREEN << "" << COLOR_RESET << std::endl;

	std::cout << "je suis au 1" << std::endl;

	if (!_request.getOneHeaders("Content-Type").find("application/x-www-form-urlencoded"))
	{
		std::cout << "je suis au 2" << std::endl;
		dbPath = _server.getRoot() + "/db/forumlaire.txt"; //TEST AVEC UN FICHIER TXT
		if (addForm(dbPath))
		{
			std::cout << "je suis au 2.1" << std::endl;
			// std::cout << "form" << std::endl; //--> Test path
			setStatusCode(INTERNAL_SERVER_ERROR);
		}

	}
	else if (!_request.getOneHeaders("Content-Type").find("multipart/form-data"))
	{
		std::cout << "je suis au 3" << std::endl;
		dbPath = _server.getRoot() + "/upload/image.png"; //TEST AVEC IMAGE

		std::cout  << "je print la request body" << _request.getBody() << std::endl;


		if (saveImage(_requestBody, _request.getBoundary(), dbPath))
		{	
			// std::cout << "image" << std::endl; //--> Test path
			setStatusCode(INTERNAL_SERVER_ERROR);
		}
	}

	if (getStatusCode() >= 400 && 500 >= getStatusCode())
	{
		setErrorBody();
		return;
	}
	getHtmlFile("/page/index.html");
}

void							Response::requestDelete()						// http request DELETE
{
	std::cout << COLOR_GREEN << "REQUEST DELETE\t🖥️   ->   🗄️\t\t" << getCurrentTimestamp() << COLOR_RESET <<std::endl;
	std::cout << COLOR_GREEN << "┌───────────────────────────────────────────────────┐" << COLOR_RESET << std::endl;
	//std::cout << COLOR_GREEN << "│ " << COLOR_RESET << _request.getRaw() << std::endl;
	std::cout << COLOR_GREEN << "└───────────────────────────────────────────────────┘" << COLOR_RESET << std::endl;
	std::cout << "" << std::endl;
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
