#include "../../include/Request.hpp"

/* -------------------- Constructeur & Destructeur --------------------*/
Request::Request(std::string &str): _method (""), _version(""), _ret(200), _body(""), _port(80), _path(""), _query(""), _raw(str)
{
	_methods.push_back("GET");
	_methods.push_back("POST");
	_methods.push_back("POST");
	resetHeaders();
	_env.clear();
}

Request::~Request() {}

/* -------------------- Operateur d'assignation --------------------*/
Request &Request::operator=(const Request &other)
{
	this->_method = other.getMethod();
	this->_version = other.getVersion();
	this->_ret = other.getRet();
	this->_body = other.getBody();
	this->_port = other.getPort();
	this->_path = other.getPath();
	this->_query = other.getQuery();
	this->_raw = other.getRaw();

	return (*this);
}

/* -------------------- Getters --------------------*/
const std::string	&Request::getMethod() const
{
	return (_method);
}

const std::string	&Request::getMethods(int index) const
{
	return (_methods[index]);
}

const std::string	&Request::getVersion() const
{
	return (_version);
}

const std::map<std::string, std::string>	&Request::getHeaders() const
{
	return (_headers);
}

const std::map<std::string, std::string>	&Request::getEnv() const
{
	return (_env);
}

int	Request::getRet() const
{
	return (_ret);
}

const std::string	&Request::getBody() const
{
	return (_body);
}

int	Request::getPort() const
{
	return (_port);
}

const std::string	&Request::getPath() const
{
	return (_path);
}

const std::string	&Request::getQuery() const
{
	return (_query);
}

const std::string	&Request::getRaw() const
{
	return (_raw);
}

/* -------------------- Setters --------------------*/
void Request::setMethod(const std::string &method)
{
	this->_method = method;
}

void Request::setBody(const std::string &line)
{
	this->_body = line;
}

void Request::setRet(int ret)
{
	this->_ret = ret;
}

/* -------------------- Initialization Methods Vector --------------------*/
std::vector<std::string>	Request::initMethods()
{
	std::vector<std::string> methods;

	methods.push_back("GET");
	methods.push_back("POST");
	methods.push_back("DELETE");

	return (methods);
}

/* -------------------- Reset Map Headers --------------------*/
void	Request::resetHeaders()
{
	this->_headers.clear();

	this->_headers["Accept-Charsets"] = "";
	this->_headers["Accept-Language"] = "";
	this->_headers["Accept-Post"] = "";
	this->_headers["Allow"] = "";
	this->_headers["Authorization"] = "";
	this->_headers["Connection"] = "Keep-Alive";
	this->_headers["Content-Language"] = "";
	this->_headers["Content-Lenght"] = "";
	this->_headers["Content-Location"] = "";
	this->_headers["Content-Type"] = "";
	this->_headers["Date"] = "";
	this->_headers["Host"] = "";
	this->_headers["Last-Modified"] = "";
	this->_headers["Location"] = "";
	this->_headers["Referer"] = "";
	this->_headers["Retry-After"] = "";
	this->_headers["Server"] = "";
	this->_headers["Transfer-Encoding"] = "";
	this->_headers["User-Agent"] = "";
	this->_headers["WWW-Authenticate"] = "";
}

/* -------------------- Parsing --------------------*/
int	Request::readFirstLine(const std::string &str)
{
	size_t index;
	std::string line;
	std::string method;

	index = str.find_first_of('\n');
	line = str.substr(0, index);
	index = str.find_first_of(' ');
	if (index == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "No space after method" << COLOR_RESET << std::endl;
		return (400);
	}
	method = line.assign(line, 0, index);
	if (method.compare(getMethods(0))
		&& method.compare(getMethods(1))
		&& method.compare(getMethods(2)))
	{
		setRet(400);
		std::cerr << COLOR_RED << "Wrong method" << COLOR_RESET << std::endl;
		return (400);
	}
	this->_method.assign(line, 0, index);
	return (this->readPath(line, index));
}

int	Request::readPath(std::string str, size_t index)
{
	size_t j;


	if ((j = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "No PATH / HTTP version" << COLOR_RESET << std::endl;
		return (400);
	}
	if ((index = str.find_first_of(' ', j)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "No HTTP version" << COLOR_RESET << std::endl;
		return (400);
	}
	this->_path.assign(str, j, index - j);
	return this->readVersion(str, index);
}

int Request::readVersion(std::string str, size_t index)
{
	if ((index = str.find_first_not_of(' ', index)) == std::string::npos)
	{
		setRet(400);
		std::cerr << COLOR_RED << "No HTTP version" << COLOR_RESET << std::endl;
		return 400;
	}
	if (!str.compare(0, 5, "HTTP/"))
		_version = str.assign(str, index + 5, 3);
	if (_version.compare("1.0") && _version.compare("1.1"))
	{
		setRet(400);
		std::cerr << COLOR_RED << "BAD HTTP VERSION (" << this->_version << ")" << COLOR_RESET << std::endl;
		return (this->_ret);
	}
}