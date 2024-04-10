#ifndef REQUEST_HPP
#define REQUEST_HPP

 #include "../define.hpp"

class Request 
{
    std::string							_method;
	std::vector<std::string>			_methods;
	std::string							_version;
	std::map<std::string, std::string>	_headers;
	std::map<std::string, std::string>	_env;
	int									_ret;
	std::string							_body;
	std::string							_port;
	std::string							_path;
	std::string							_query;
	std::string							&_raw;

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
    public:
    // Constructeur et destructeur
        Request(std::string &str);
        ~Request();

	// Copie d'assignation
        Request										&operator=(const Request &other);


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

	// Utils
		void										resetHeaders();
		// void										stripAll();
		void										displayHeaders() const;
		// std::string									readKey(std::string &str);
		// std::string									readValue(std::string &str);

		static	std::vector<std::string>			initMethods();
};

std::ostream	&operator<<(std::ostream& out, const Request& request);
#endif
