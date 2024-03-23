#ifndef _DEFINE_HPP
#define _DEFINE_HPP

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

// Fichier de configuration du serveur
const std::string config_file = "./config/webserv.conf";

// Couleur pour les print
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_RESET "\033[0m"

// Code d etas des reponses http///////////////////////////////////////
enum HttpStatus{
    // success
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    // redirection
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    not_modified = 304,
    // client error
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    // error server
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
};

#endif
