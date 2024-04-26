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
