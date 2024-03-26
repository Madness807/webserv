#include "../../include/define.hpp"
#include "../../include/Request.hpp"

std::string Request::readKey(std::string &str)
{
	std::string ret;

	size_t index = str.find_first_of(':');
	ret.append(str, 0, index);
	return (ret);
}