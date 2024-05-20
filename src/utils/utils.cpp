#include "../../include/utils/utils.hpp"

std::string trim(const std::string& str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isspace(*it, std::locale::classic())) ++it;

    std::string::const_reverse_iterator rit = str.rbegin();
    while (rit.base() != it && std::isspace(*rit, std::locale::classic())) ++rit;

    return std::string(it, rit.base());
}

std::string getCurrentTimestamp() {
	char buffer[20];
	time_t now = time(0);
	struct tm *timeinfo = localtime(&now);

	// Format: YYYY-MM-DD HH:MM:SS
	strftime(buffer, 20, "%H:%M:%S", timeinfo);

	return std::string(buffer);
}

int	pathIsFile(const std::string &path)
{
	struct stat s;
	if (stat(path.c_str(), &s) == 0 )
	{
		if (s.st_mode & S_IFDIR)
			return 0;
		else if (s.st_mode & S_IFREG)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int hasWritePermission(const std::string &path)
{
    struct stat s;
    if (stat(path.c_str(), &s) != 0)
        return (0);

    // Vérifie les permissions d'écriture pour l'utilisateur, le groupe et les autres
    if (s.st_mode & S_IWUSR || s.st_mode & S_IWGRP || s.st_mode & S_IWOTH)
        return (1);
    
    return (0);
}