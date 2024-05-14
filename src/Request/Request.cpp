#include "../include/Request/Request.hpp"

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
Request::Request() {}

Request::Request(std::string &str, ServerConfig server): _method (""), _version(""), _ret(200), _body(""), _port("80"), _path(""), _query(""), _raw(str)
{
	_bodySize = std::atoi(server.getMaxBodySize().c_str());
	this->_methods = this->initMethods();
	this->resetHeaders();
	this->_env_cgi.clear();
	this->parse(str);
	if (this->getRet() != 200)
		std::cerr << "\t\t\t\t\t\t\t     =======> 🔻 " 
			<< COLOR_RED << "Parse error: " << this->getRet() << COLOR_RESET << std::endl;
}

Request::~Request() {}

//##################################################################
//		constructeur par copie et operateur d'affectation		   #
//##################################################################
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

Request::Request(const Request &other)
{
	*this = other;
}

//##################################################################
//                          GETTERS                                #
//##################################################################
const std::string	&Request::getMethod() const{
	return (_method);
}
const std::string	&Request::getVersion() const{
	return (_version);
}
const std::map<std::string, std::string>	&Request::getHeaders() const{
	return (_headers);
}
const std::map<std::string, std::string>	&Request::getEnv() const{
	return (_env_cgi);
}
int	Request::getRet() const{
	return (_ret);
}
const std::string	&Request::getBody() const{
	return (_body);
}
const std::string	Request::getPort() const{
	return (_port);
}
const std::string	&Request::getPath() const{
	return (_path);
}
const std::string	&Request::getQuery() const{
	return (_query);
}
const std::string	&Request::getRaw() const{
	return (_raw);
}
const std::string	&Request::getOneHeaders(const std::string &key){
	return (_headers[key]);
}
const std::string	&Request::getBoundary() const
{
	return (_boundary);
}

//##################################################################
//                          SETTERS                                #
//##################################################################
void Request::setMethod(const std::string &method)
{
	this->_method = method;
}

void Request::setBody(const std::string &line)
{
	// if (line.length() > _bodySize)
	// {
	// 	setRet(413);
	// 	return;
	// }
	_body = line;
}

void Request::setRet(int ret)
{
	this->_ret = ret;
}

void Request::setBoundary(const std::string &content_type)
{
	size_t startPos;
	startPos = content_type.find("=") + 1;
	_boundary = content_type.substr(startPos);
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
	this->_headers["Connection"] = "";
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
	this->_headers["Filename"] = "";
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

