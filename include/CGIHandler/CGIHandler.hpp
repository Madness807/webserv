#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <string>
#include <map>
#include <vector>
#include "../define.hpp"

#define BUFFERSIZE 20000

class CGIHandler {
	public:
		// constructeur et destructeur
		CGIHandler();
		CGIHandler(std::string path);
		// CGIHandler(const std::string& scriptPath, const std::map<std::string, std::string>& initialEnv);
		~CGIHandler();

		// Méthodes///////////////////
		int		execute();
		//void		execute(const std::vector<char>& requestBody);	// exécute le CGI

		// Getters
		std::string		getBody() const;
		std::string		getHeader() const;
		std::string		getPath() const;
		std::string		getCgiContentType() const;

	private:
		std::string							_path;					// chemin du fichier CGI
		std::map<std::string, std::string>	_env;					// environnement CGI
		std::string							_header;			// corps de la requête
		std::string							_body;
		std::string							_cgiContentType;		// contenu du CGI

		// Méthodes///////////////////
		void			setupEnv();														// initialise l'environnement CGI
		std::string		readOutput();													// lit la sortie du CGI
		int				createPipe(const std::vector<char>& requestBody, int& outFd);	// crée un pipe
		//void			launchCGI(CGIHandler &cgiHandler);									// lance le CGI
		int				launchChild(int *fd, const char** args);
		int				launchParent(int *fd, int pid);
		int				findHeadAndBody(std::string buf);
		// Setters

													// getter du chemin du fichier CGI

};

#endif
