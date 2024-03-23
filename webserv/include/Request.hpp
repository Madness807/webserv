#ifndef REQUEST_HPP
#define REQUEST_HPP

// CPP Includes
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <string>
# include <limits>
# include <cstdio>

// CPP Containers
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <iterator>
# include <list>
# include <utility>

// C Includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <errno.h>
# include <dirent.h>

// C System
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>

// C Network
# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netinet/in.h>

class Request 
{
    std::string									_method;
	std::string									_version;
	std::map<std::string, std::string>			_headers;
	std::map<std::string, std::string>			_env;
	int											_ret;
	std::string									_body;
	int											_port;
	std::string									_path;
	std::string									_query;
	std::string									&_raw;
    
    public:
    // Constructeur et destructeur
        Request(std::string &str);
        ~Request();

	// Copie d'assignation
        Request &operator=(const Request &other);

    // Setters
		void setMethod(const std::string &method);
		void setBody(const std::string& line);
		void setRet(int);

    // Getters
		const std::string									&getMethod() const;
		const std::string									&getVersion() const;
        const std::map<std::string, std::string>			&getHeaders() const;
		const std::map<std::string, std::string>			&getEnv() const;
		int													getRet() const;
		const std::string									&getBody() const;
		int													getPort() const;
		const std::string									&getPath() const;
		const std::string									&getQuery() const;
		const std::string									&getRaw() const;

	// Utils
		int		parse(const std::string& str);
		void	resetHeaders();
		void	stripAll();
		void	displayHeaders() const;

		static std::vector<std::string>		initMethods();
};

std::ostream	&operator<<(std::ostream& out, const Request& request);
#endif
