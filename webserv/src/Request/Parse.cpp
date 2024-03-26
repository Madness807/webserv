#include "../../include/Request.hpp"

/* ++++++++++++++++++++++++++++++++++++++++ Parsing ++++++++++++++++++++++++++++++++++++++++ */
/* -------------------- Read First Line function --------------------*/
int	Request::readFirstLine(const std::string &str)
{
	size_t index;
	std::string line;

	index = str.find_first_of("\r\n");
	line = str.substr(0, index);
	index = str.find_first_of(' ');
	if (index == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "1.1 No space after method" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
    this->_method.assign(line, 0, index);
    return (this->readPath(line, index));
}

/* -------------------- Read Path function --------------------*/
int	Request::readPath(std::string str, size_t index)
{
	size_t j;


	if ((j = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "2.1 No PATH / HTTP version" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
	if ((index = str.find_first_of(' ', j)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "2.2 No HTTP version" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
	this->_path.assign(str, j, index - j);
	return (this->readVersion(str, index));
}

/* -------------------- Check Method function --------------------*/
int	Request::checkMethod()
{
	for (size_t index = 0; index < getMethod().size(); index++)
		if (this->_methods[index] == this->getMethod())
			return (this->getRet());
	std::cerr << COLOR_RED << "Invalide Method" << COLOR_RESET << std::endl;
	this->setRet(400);
	return (this->getRet());
}

/* -------------------- Read Version function --------------------*/
int Request::readVersion(std::string str, size_t index)
{
	if ((index = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "3.1 No HTTP version" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
	if (str[index] == 'H' && str[index + 1] == 'T' && str[index + 2] == 'T' && str[index + 3] == 'P' && str[index + 4] == '/' )
		this->_version.assign(str, index + 5, 3);
	if (!this->_version.compare("1.0") && !this->_version.compare("1.1"))
	{
		setRet(400);
		std::cerr << COLOR_RED << "3.2 BAD HTTP VERSION (" << this->_version << ")" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
    return (this->checkMethod());
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
    return (tmp);
}    
/* -------------------- Parse function --------------------*/
int	Request::parse(const std::string &str)
{
	std::string key;
	std::string value;
	std::string line;
    // size_t index = 0;

    std::cout << "-------------------------------------------------------------------" << std::endl;
    this->readFirstLine(str);
    std::cout << "-------------------------------------------------------------------" << std::endl;
	// while ((line = nextLine(str, index)) !=  "\r" && line != "" && this->getRet() != 400)
	// {
	// 	std::cout << line << std::endl;
	// }
    return (1);
}

std::ostream	&operator<<(std::ostream &out, const Request &request)
{
	std::map<std::string, std::string>::const_iterator it;

	out << "Method: " << request.getMethod();
	out << " | HTTP version: " << request.getVersion() << std::endl;
	out << "Port: " << request.getPort() << std::endl;
	out << "Path: " << request.getPath() << std::endl;

	for (it = request.getHeaders().begin(); it != request.getHeaders().end(); it++)
		out << it->first << " : " << it->second << std::endl;
	out << std::endl << "Request body :" << std::endl << request.getBody() << std::endl;

	return (out);
}