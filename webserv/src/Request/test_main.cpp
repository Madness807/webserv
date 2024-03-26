#include "../../include/define.hpp"
#include "../../include/Request.hpp"

int main( int ac, char **av)
{
    (void) ac;
    std::string buffer = av[1];
    Request test(buffer);
    std::ifstream inFile(buffer.c_str());

    while (std::getline(inFile, buffer))
        test.parse(buffer);

    return (1);
}