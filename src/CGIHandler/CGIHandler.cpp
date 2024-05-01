#include "../../include/CGIHandler/CGIHandler.hpp"
#include <unistd.h>

//##################################################################
//                   Constructor && Destructor                     #
//##################################################################
CGIHandler::CGIHandler(){}

// CGIHandler::CGIHandler(const std::string& scriptPath, const std::map<std::string, std::string>& initialEnv){}

CGIHandler::~CGIHandler(){}

//##################################################################
//                          SETTERS                                #
//##################################################################
void CGIHandler::setBodyResponse(std::string bodyResponse)
{
	this->_bodyResponse = bodyResponse;
}
//##################################################################
//                          GETTERS                                #
//##################################################################
std::string CGIHandler::getBodyResponse() const
{
	return this->_bodyResponse;
}
//##################################################################
//                           Methodes                              #
//##################################################################


std::string CGIHandler::execute()
{
	int pid, status;
	int reading = 0;
	std::string buf;
	char tmp[200];
	//extern char** environ;
	const char *args[] = {"/usr/bin/python3", "/Users/jdefayes/documents/git/Cursus/webserv/src/CGIHandler/test.py", NULL};

	int fd[2];

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
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		execve(args[0], const_cast<char**>(args), NULL);
		perror("Excve : ");
	}

	else//parent
	{
		waitpid(0, &status, 0);// 0 == tous les process child issu du meme process, ,
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		do
		{
			memset(tmp, 0, sizeof(tmp));
			reading = read(fd[0], &tmp, 1);
			if (reading > 0)
			{
				buf.append(tmp, reading);
			}
		}
		while (reading > 0);

		setBodyResponse(buf);
		std::cout << "Check _bodyResponse: " << this->getBodyResponse() << std::endl;
		close(fd[0]);
	}

	return(buf);
}

std::string CGIHandler::execute(const std::vector<char>& requestBody)
{
	std::string test;
	(void)requestBody;
	return (test);
}


//void CHIHandlersetupEnv()
//{}

// std::string CGIHandler::readOutput()
// {}

// int CGIHandler::createPipe(const std::vector<char>& requestBody, int& outFd)
// {}


/*

	pipe(int fds[2]);

	Parameters :
	fd[0] will be the fd(file descriptor) for the
	read end of pipe.
	fd[1] will be the fd for the write end of pipe.

	Returns : 0 on Success.
	-1 on error.


	client envoie requete au serveur (socket part)
	serveur envoie la requeste au parsing
	on determine si c est une demande statique ou dynamique (CGI, extension .py)
	execute et renvoi de la response au serveur

	ensuite wait pid et recupere, read ce qu i  y a dans le pipe
*/


