#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../define.hpp"

class Request
{
    std::string							_method;
	std::vector<std::string>			_methods;
	std::string							_version;
	std::map<std::string, std::string>	_headers;
	std::map<std::string, std::string>	_env_cgi;
	int									_ret;
	std::string							_body;
	size_t								_bodySize;
	std::string							_port;
	std::string							_path;
	std::string							_query;
	std::string							_raw;
	std::string							_boundary;

	//Parsing
	int									parse(const std::string &str);
	int									readFirstLine(const std::string &str);
	int									readPath(std::string str, size_t index);
	int									readVersion(std::string str, size_t index);
	std::string							nextLine(const std::string &str, size_t &index);
	int									checkMethod();
	void								findQuery();

    // Setters
	void								setMethod(const std::string &method);
	void								setBody(const std::string &line);
	void								setRet(int ret);
	void								setBoundary(const std::string &content_type);
    public:
    // Constructeur et destructeur
		Request();
        Request(std::string &str);
        ~Request();

	// Copie d'assignation
        Request										&operator=(const Request &other);
		Request(const Request &other);

    // Getters
		const std::string							&getMethod() const;
		const std::string							&getVersion() const;
        const std::map<std::string, std::string>	&getHeaders() const;
		const std::string							&getOneHeaders(const std::string &key);
		const std::map<std::string, std::string>	&getEnv() const;
		int											getRet() const;
		const std::string							&getBody() const;
		const std::string							getPort() const;
		const std::string							&getPath() const;
		const std::string							&getQuery() const;
		const std::string							&getRaw() const;
		const std::string							&getBoundary() const;

	// Utils
		void										resetHeaders();
		void										displayHeaders() const;

		static	std::vector<std::string>			initMethods();
};

std::ostream	&operator<<(std::ostream& out, const Request& request);

#endif
