 #include "../include/ConfigParser/ConfigParser.hpp"
 #include "../include/ConfigParser/ServerConfig.hpp"
 #include "../include/verbose/verbose.hpp"
 #include "../include/define.hpp"

   #include <iostream>
   #include <fstream>
   #include <vector>
   #include <string>
   #include <map>
   #include <list>
   
 void printSRVConfig(ServerConfig *serverconfig)
 {
    //Print the server config
    std::cout << "\033[31m#####################################################\033[0m" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "\033[31mSERVERCONFIG-------------------------\033[0m" << std::endl;
    std::cout << "Server Name:\t\t" << serverconfig->getServerName() << std::endl;
    std::cout << "Server IP:\t\t" << serverconfig->getIp() << std::endl;
    std::cout << "Server Port:\t\t" << serverconfig->getPort() << std::endl;
    std::cout << "Server Max Body Size:\t" << serverconfig->getMaxBodySize() << std::endl;
    std::cout << "Server Default File:\t" << serverconfig->getDefaultFile() << std::endl;
    std::cout << "Server Error Page:\t" << serverconfig->getErrorPage() << std::endl;
    std::cout << "Server Root:\t\t" << serverconfig->getRoot() << std::endl;

    //Print the location config
    int size1 = serverconfig->getLocationConfig("/").getMethods().size();
    int i = 0;
    std::cout << "" << std::endl;
    std::cout << "\033[31mLOCATIONCONFIG-------------------------\033[0m" << std::endl;
    std::cout << "\033[1;34mLOCATION 1\033[0m" << std::endl;
    std::cout << "\033[1;34m----------\033[0m" << std::endl;
    std::cout << "Path:\t\t\t" << serverconfig->getLocationConfig("/").getPath() << std::endl;
    std::cout << "Redirection:\t\t" << serverconfig->getLocationConfig("/").getRedirect() << std::endl;
    std::cout << "DirectoryListing:\t" << serverconfig->getLocationConfig("/").getDirectoryListing() << std::endl;
    while (i < size1)
    {
        std::cout << "Methods:\t\t" << serverconfig->getLocationConfig("/").getMethods().at(i) << std::endl;
        i++;
    }    
    std::cout << "" << std::endl;

    int size2 = serverconfig->getLocationConfig("/uploads").getMethods().size();
    i = 0;
    std::cout << "\033[1;34mLOCATION 2\033[0m" << std::endl;
    std::cout << "\033[1;34m----------\033[0m" << std::endl;
    std::cout << "Path:\t\t\t" << serverconfig->getLocationConfig("/uploads").getPath() << std::endl;
    std::cout << "Redirection:\t\t" << serverconfig->getLocationConfig("/uploads").getRedirect() << std::endl;
    std::cout << "DirectoryListing:\t" << serverconfig->getLocationConfig("/uploads").getDirectoryListing() << std::endl;
    while (i < size2)
    {
        std::cout << "Methods:\t\t" << serverconfig->getLocationConfig("/uploads").getMethods().at(i) << std::endl;
        i++;
    }  
    std::cout << "" << std::endl;


    int size3 = serverconfig->getLocationConfig("/home.html").getMethods().size();
    i = 0;
    std::cout << "\033[1;34mLOCATION 3\033[0m" << std::endl;
    std::cout << "\033[1;34m----------\033[0m" << std::endl;
    std::cout << "Path:\t\t\t" << serverconfig->getLocationConfig("/home.html").getPath() << std::endl;
    std::cout << "Redirection:\t\t" << serverconfig->getLocationConfig("/home.html").getRedirect() << std::endl;
    std::cout << "DirectoryListing:\t" << serverconfig->getLocationConfig("/home.html").getDirectoryListing() << std::endl;
    while (i < size3)
    {
        std::cout << "Methods:\t\t" << serverconfig->getLocationConfig("/uploads").getMethods().at(i) << std::endl;
        i++;
    }  
    std::cout << "" << std::endl;
    std::cout << "\033[31m#####################################################\033[0m" << std::endl;

 }

