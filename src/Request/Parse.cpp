#include "../../include/Request/Request.hpp"

/* ++++++++++++++++++++++++++++++++++++++++ Parsing ++++++++++++++++++++++++++++++++++++++++ */
/* -------------------- Read First Line function --------------------*/
int	Request::readFirstLine(const std::string &str)
{
	size_t		index;
	std::string	line;

	index = str.find_first_of('\n');
	line = str.substr(0, index);
	index = str.find_first_of(' ');
	if (index == std::string::npos)
	{
		setRet(BAD_REQUEST);
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "1.1 No space after method"
			<< COLOR_RESET << std::endl;
		return (getRet());
	}
    this->_method.assign(line, 0, index);
	std::vector<std::string>::iterator it = std::find(_methods.begin(), _methods.end(), getMethod());
	if (it == _methods.end())
	{
		setRet(BAD_REQUEST);
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "1.2 Wrong Method"
			<< COLOR_RESET << std::endl;
		return (getRet());
	}
    return (this->readPath(line, index));
}

/* -------------------- Read Path function --------------------*/
int	Request::readPath(std::string str, size_t index)
{
	size_t j;


	if ((j = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(BAD_REQUEST);
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "2.1 No PATH / HTTP version"
			<< COLOR_RESET << std::endl;
		return (getRet());
	}
	if ((index = str.find_first_of(' ', j)) == std::string::npos)
	{
		setRet(BAD_REQUEST);
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "2.2 No HTTP version"
			<< COLOR_RESET << std::endl;
		return (getRet());
	}
	
	this->_path.assign(str, j, index - j);
	return (this->readVersion(str, index));
}

/* -------------------- Read Version function --------------------*/
int Request::readVersion(std::string str, size_t index)
{
	if ((index = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(BAD_REQUEST);
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "3.1 No HTTP version"
			<< COLOR_RESET << std::endl;
		return (this->_ret);
	}
	if (str[index] == 'H' && str[index + 1] == 'T' && str[index + 2] == 'T' && str[index + 3] == 'P' && str[index + 4] == '/' )
		this->_version.assign(str, index + 5, 3);
	if (this->_version.compare("1.0") && this->_version.compare("1.1"))
	{
		setRet(BAD_REQUEST);
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "3.2 BAD HTTP VERSION (" << this->_version << ")"
			<< COLOR_RESET << std::endl;
		return (this->_ret);
	}
    return (this->checkMethod());
}

/* -------------------- Check Method function --------------------*/
int	Request::checkMethod()
{
	for (size_t index = 0; index < getMethod().size(); index++)
		if (this->_methods[index] == this->getMethod())
			return (this->getRet());
	std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " << COLOR_RED << "Invalide Method"
		<< COLOR_RESET << std::endl;
	this->setRet(BAD_REQUEST);
	return (this->getRet());
}

/* -------------------- Next Line function --------------------*/
std::string Request::nextLine(const std::string &str, size_t &index)
{
    std::string tmp;
    size_t      j;
    if (index == std::string::npos)
        return ("");
    j = str.find_first_of('\n', index);
    tmp = str.substr(index, j - index);
	if (j == std::string::npos)
		index = j;
	else
		index = j + 1;
    return (tmp);
}    
/* -------------------- Parse function --------------------*/
int	Request::parse(const std::string &str)
{
	std::string key;
	std::string value;
	std::string line;
    size_t		i = 0;
	size_t		j = 0;

	_bodySize = str.length();
    this->readFirstLine(nextLine(str, i));
	while ((line = nextLine(str, i)) != "\r" && line != "" && this->_ret != 400)
	{
		j = line.find_first_of(':');
		key = line.substr(0, j);
		value = line.substr(j + 2, line.size()); //--> possible erreur a voir dans le futur;
		this->_headers[key] = value;
		if (key == "Host")
		{
			j = line.find_first_of(':', j + 1);
			value = line.substr(j + 1, line.size());
			this->_port = value;
		}
	}
	if (this->_headers["Www-Authenticate"] != "")
			this->_env_cgi["Www-Authenticate"] = this->_headers["Www-Authenticate"];
	this->setBody(str.substr(i, std::string::npos));
	// this->setBody(str.substr(i));
	this->findQuery();
	if (!getOneHeaders("Content-Type").find("multipart/form-data"))
		this->setBoundary(getOneHeaders("Content-Type"));
    return (this->getRet());
}

std::ostream	&operator<<(std::ostream &out, const Request &request)
{
	std::map<std::string, std::string>::const_iterator it;

	out << "" << std::endl;
    out << COLOR_GREEN << " # RESULTAT DU PARSING DES REQUETES HTTP" << COLOR_RESET << std::endl;
    out << std::endl;
	out << "Method: " << request.getMethod();
	out << " | HTTP version: " << request.getVersion() << std::endl;
	out << "Port: " << request.getPort() << std::endl;
	out << "Path: " << request.getPath() << std::endl;
	out << "Query: " << request.getQuery() << std::endl;
	out << "Boundary: " << request.getBoundary() << std::endl;
	// out << "Raw: " << request.getRaw() << std::endl;

	out << COLOR_BLUE << "HEADER" << COLOR_RESET << std::endl;
	out << COLOR_BLUE << "-------" << COLOR_RESET << std::endl;
	for (it = request.getHeaders().begin(); it != request.getHeaders().end(); it++)
		out << COLOR_RED << it->first << COLOR_RESET << " : " << it->second << std::endl;
	
	out << "" << std::endl;
	out << COLOR_BLUE << "BODY" << COLOR_RESET << std::endl;
	out << COLOR_BLUE << "-----" << COLOR_RESET;


	out << std::endl << "Request body :" << std::endl << request.getBody() << std::endl;

	// out << "\nCode status on Request: " << request.getRet() << std::endl;

	return (out);
}

