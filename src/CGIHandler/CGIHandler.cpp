#include "../../include/CGIHandler/CGIHandler.hpp"
#include <unistd.h>

#include <stdio.h>

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
CGIHandler::CGIHandler(){}

CGIHandler::CGIHandler(std::string path)
{
    this->_path = path;
}

CGIHandler::~CGIHandler(){}

//##################################################################
//                          SETTERS                                #
//##################################################################

//##################################################################
//                          GETTERS                                #
//##################################################################
std::string CGIHandler::getBody() const
{
	return this->_body;
}

std::string CGIHandler::getHeader() const
{
	return this->_header;
}

std::string CGIHandler::getPath() const
{
	return this->_path;
}

std::string CGIHandler::getCgiContentType() const {
    std::istringstream headerStream(_header); // Créez un flux à partir de _header pour lire ligne par ligne
    std::string line;

    while (std::getline(headerStream, line)) { // Lisez chaque ligne dans 'line'

	std::cout << "je print la ligne" << line << std::endl;
	std::cout << "" << std::endl;

        if (line.find("Content-Type") != std::string::npos) {
            size_t startPos = line.find(":") + 1; // Trouvez la position du début du type de contenu
            // Supprimez les espaces blancs au début
            while (startPos < line.length() && isspace(line[startPos])) {
                startPos++;
            }
            return line.substr(startPos); // Retournez le type de contenu
        }
    }
    return ""; // Retournez une chaîne vide si le type de contenu n'est pas trouvé
}

//##################################################################
//                           Methodes                              #
//##################################################################

int CGIHandler::execute()
{
	int pid;
	int fd[2];
	const char* tmpPath = _path.c_str();
	const char *args[] = {"/usr/bin/python3", tmpPath, NULL};
	int exitStatus;

	if(pipe(fd) == -1)
	{
		perror("Pipe");
		exit(-1);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("Fork");
		exit(-1);
	}
	if(pid == 0) // child
	{
		launchChild(fd, args);
	}
	else // parent
	{
		exitStatus = launchParent(fd, pid);
	}
	//std::cout << "exitStatus : " << exitStatus << std::endl;
	return(exitStatus);
}


int CGIHandler::launchChild(int *fd, const char** args)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(args[0], const_cast<char**>(args), NULL);
	exit(-1);
}

int CGIHandler::launchParent(int *fd, int pid)
{
	int status;
	int reading = 0;
	char tmp[20000];
	int exitStatus;

	waitpid(pid, &status, 0); // Attendez le processus enfant spécifique
	if(WIFEXITED(status))
	{
		exitStatus = WEXITSTATUS(status); // tout c est bien passe, enfnt a quitte meme si excve a echoue
		if (exitStatus != 0)
			return(500);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	std::string buf;
	do
	{
		memset(tmp, 0, sizeof(tmp));
		ssize_t reading = read(fd[0], tmp, sizeof(tmp) - 1); // Utilisez sizeof(tmp) pour éviter de lire au-delà de la taille du tampon
		if (reading > 0)
		{
			buf.append(tmp, reading);
		}
	}
	while (reading > 0);

	findHeadAndBody(buf);
	close(fd[0]);
	
	return (exitStatus);
}

int CGIHandler::findHeadAndBody(std::string buf)
{
	// Trouvez la position de la séquence de deux sauts de ligne (\n\r\n)
	size_t headerEndPos = buf.find("\n\n");
	if (headerEndPos != std::string::npos)
	{
		// Divisez la sortie en en-tête et corps
		_header = buf.substr(0, headerEndPos);
		_body = buf.substr(headerEndPos + 2); // +4 pour passer la séquence de deux sauts de ligne
	}
	else
	{
		// Si la séquence de deux sauts de ligne n'est pas trouvée, traitez toute la sortie comme du corps
		_body = buf;
	}
	return(0);
}
