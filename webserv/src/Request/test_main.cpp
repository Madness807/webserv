#include "../../include/define.hpp"
#include "../../include/Request.hpp"

int main( int ac, char **av)
{
    (void) ac;
    (void) av;
    std::string buffer = "GET /index.html?blabla=blabla+bla=bla+inc=inc HTTP/1.1\r\nHost: example.com:8080\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nCookie: userId=12345; sessionId=67890\r\n\r\nbody: {bla}\r\n";
    // std::string buffer = av[1];
    // std::ifstream inFile(buffer.c_str());

    // while (std::getline(inFile, buffer))
    // {
        Request test(buffer);
        std::cout << test << std::endl;
    // }
    return (1);
}