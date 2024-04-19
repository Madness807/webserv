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

		// GETTERS
		std::string getPath();
		std::vector<std::string> getMethods();
		std::string getRedirect();
		bool getDirectoryListing();

		// Méthodes
		void addMethod(std::string method);
		
};

#endif
