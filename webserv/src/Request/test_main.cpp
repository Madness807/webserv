#include "../../include/define.hpp"
#include "../../include/Request.hpp"

int main( int ac, char **av)
{
    (void) ac;
    std::string buffer = av[1];
    std::ifstream inFile(buffer.c_str());

    while (std::getline(inFile, buffer))
    {
        Request test(buffer);
        std::cout << test << std::endl;
    }
    return (1);
}