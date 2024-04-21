#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

// #include <string>
// #include <map>
// #include <list>
// #include <iostream>
// #include <vector>
// #include <sstream>
#include "../define.hpp"
#include "../utils/utils.hpp"

class LocationConfig{
	private:

		std::string _path;
		std::string _redirect;
		std::string cgiPath;
		std::string cgiExtension;
		std::vector<std::string> _methods;
		bool _directory_listing;
		
	public:
		// constructeur et destructeur
			LocationConfig();
			~LocationConfig();

		// SETTERS
		void setPath(std::string path);
		void setMethods(const std::vector<std::string> methods);
		void setRedirect(std::string redirect);
		void setDirectoryListing(bool directory_listing);
		void setCgiPath(std::string path);
		void setCgiExtension(std::string extension);

		// GETTERS
		std::string getPath() const;
		std::vector<std::string> getMethods() const;
		std::string getRedirect() const;
		bool getDirectoryListing()const;
		std::string getCgiPath() const;
		std::string getCgiExtension() const;

		// Méthodes
		void addMethod(std::string method);
		
};

#endif
