#ifndef REQUEST_HPP
#define REQUEST_HPP

 #include "define.hpp"

class Request 
{
    std::string							_method;
	std::string							_version;
	std::map<std::string, std::string>	_headers;
	std::map<std::string, std::string>	_env;
	int									_ret;
	std::string							_body;
	int									_port;
	std::string							_path;
	std::string							_query;
	std::string							&_raw;

	//Parsing
	int									readFirstLine(const std::string &str);
    
    public:
    // Constructeur et destructeur
        Request(std::string &str);
        ~Request();

	// Copie d'assignation
        Request										&operator=(const Request &other);

    // Setters
		void										setMethod(const std::string &method);
		void										setBody(const std::string &line);
		void										setRet(int ret);

    // Getters
		const std::string							&getMethod() const;
		const std::string							&getVersion() const;
        const std::map<std::string, std::string>	&getHeaders() const;
		const std::map<std::string, std::string>	&getEnv() const;
		int											getRet() const;
		const std::string							&getBody() const;
		int											getPort() const;
		const std::string							&getPath() const;
		const std::string							&getQuery() const;
		const std::string							&getRaw() const;

	// Utils
		int											parse(const std::string& str);
		void										resetHeaders();
		void										stripAll();
		void										displayHeaders() const;

		static	std::vector<std::string>			initMethods();
};

std::ostream	&operator<<(std::ostream& out, const Request& request);
#endif
