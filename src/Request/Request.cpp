#include "../include/Request/Request.hpp"

/* -------------------- Constructeur & Destructeur --------------------*/
Request::Request(std::string &str): _method (""), _version(""), _ret(200), _body(""), _port("80"), _path(""), _query(""), _raw(str)
{
	this->_methods = this->initMethods();
	this->resetHeaders();
	this->_env.clear();
	this->parse(str);
	if (this->getRet() != 200)
		std::cerr << COLOR_RED << "Parse error: " << this->getRet() << COLOR_RESET << std::endl;
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

const std::string	Request::getPort() const
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

void				Request::findQuery()
{
	size_t		i;

	i = this->_path.find_first_of('?');
	if (i != std::string::npos)
	{
		this->_query.assign(this->_path, i + 1, std::string::npos);
		this->_path = this->_path.substr(0, i);
	}
}

