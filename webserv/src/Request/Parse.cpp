#include "../../include/Request.hpp"

/* ++++++++++++++++++++++++++++++++++++++++ Parsing ++++++++++++++++++++++++++++++++++++++++ */
/* -------------------- Read First Line function --------------------*/
int	Request::readFirstLine(const std::string &str)
{
	size_t index = 0;
	std::string line;
	std::string method;
	std::vector<std::string> methods = initMethods();

    std::cout << "Index before: " << index << std::endl;
	index = str.find_first_of('\n', 0);
    std::cout << "Index after: " << index << std::endl;
    std::cout << "ReadFirstLine: " << str << std::endl << std::endl;
	line = str.substr(0, index);
	index = str.find_first_of(' ');
    std::cout << "line: " << line << std::endl << std::endl;
	if (index == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "1.1 No space after method" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
	method = line.assign(line, 0, index);
    for (size_t i = 0; i < methods.size(); i++)
    {
	    if (method.compare(methods[i]))
	    {
            this->_method.assign(line, 0, index);
            return (this->readPath(line, index));
	    }
    }
	setRet(400);
	std::cerr << COLOR_RED << "1.2 Wrong method" << COLOR_RESET << std::endl;
	return (this->_ret);
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

/* -------------------- Read Version function --------------------*/
int Request::readVersion(std::string str, size_t index)
{
	if ((index = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "3.1 No HTTP version" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
	if (!str.compare(0, 5, "HTTP/"))
		_version = str.assign(str, index + 5, 3);
	if (_version.compare("1.0") && _version.compare("1.1"))
	{
		setRet(400);
		std::cerr << COLOR_RED << "3.2 BAD HTTP VERSION (" << this->_version << ")" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
    return (this->getRet());
}

/* -------------------- Next Line function --------------------*/
std::string Request::nextLine(std::string &str, size_t &index)
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
int	Request::parse(std::string &str)
{
	std::string buffer;
    // size_t index = 0;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    this->readFirstLine(str);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    return (1);
}