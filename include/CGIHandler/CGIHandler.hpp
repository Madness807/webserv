#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <string>
#include <map>
#include <vector>
#include "../define.hpp"

class CGIHandler {
	public:
		// constructeur et destructeur
		CGIHandler();
		// CGIHandler(const std::string& scriptPath, const std::map<std::string, std::string>& initialEnv);
		~CGIHandler();

		// Méthodes///////////////////
		std::string		execute();
		std::string		execute(const std::vector<char>& requestBody);	// exécute le CGI

	private:
		std::string							_path;					// chemin du fichier CGI
		std::map<std::string, std::string>	_env;					// environnement CGI
		std::string							_bodyResponse;

		// Méthodes///////////////////
		void			setupEnv();														// initialise l'environnement CGI
		std::string		readOutput();													// lit la sortie du CGI
		int				createPipe(const std::vector<char>& requestBody, int& outFd);	// crée un pipe
		// Setters
		void			setBodyResponse(std::string bodyResponse);

		// Getters
		std::string		getBodyResponse() const;
};

#endif
