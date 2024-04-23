 #include "../include/verbose/verbose.hpp"
 #include "../include/define.hpp"

 void printSRVConfig(ServerConfig *serverconfig)
 {
	//Print the server config
	std::cout << COLOR_RED << "┌SERVER CONFIG ───────────────────────────────────────────────┐"                                        << COLOR_RESET << std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "Name:\t\t\tt"           << serverconfig->getServerName()   <<  std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "IP:\t\t\t"             << serverconfig->getIp()            << std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "Port:\t\t\t"           << serverconfig->getPort()          <<  std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "Max Body Size:\t"    << serverconfig->getMaxBodySize()     <<  std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "Default File:\t\t"     << serverconfig->getDefaultFile()   <<  std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "Error Page:\t\t"       << serverconfig->getErrorPage()     << std::endl;
	std::cout << COLOR_RED << "│ " << COLOR_RESET << "Root:\t\t\t"           << serverconfig->getRoot()          << std::endl;

	int size1 = serverconfig->getLocationConfig("/").getMethods().size();
	int i = 0;
	std::cout << "" << std::endl;
	std::cout << COLOR_BLUE		<< "LOCATION 1" << COLOR_RESET	<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Path:\t\t\t" 			<< serverconfig->getLocationConfig("/").getPath() 				<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Redirection:\t\t" 		<< serverconfig->getLocationConfig("/").getRedirect() 			<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "DirectoryListing:\t" 	<< serverconfig->getLocationConfig("/").getDirectoryListing() 	<< std::endl;
	while (i < size1)
	{
		std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Methods:\t\t" << serverconfig->getLocationConfig("/").getMethods().at(i) << std::endl;
		i++;
	}    
	std::cout << "" << std::endl;

	int size2 = serverconfig->getLocationConfig("/uploads").getMethods().size();
	i = 0;
	std::cout << COLOR_BLUE		<< "LOCATION 1" << COLOR_RESET	<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Path:\t\t\t" 			<< serverconfig->getLocationConfig("/uploads").getPath() 				<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Redirection:\t\t" 		<< serverconfig->getLocationConfig("/uploads").getRedirect() 			<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "DirectoryListing:\t" 	<< serverconfig->getLocationConfig("/uploads").getDirectoryListing() 	<< std::endl;
	while (i < size2)
	{
		std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Methods:\t\t" << serverconfig->getLocationConfig("/uploads").getMethods().at(i) << std::endl;
		i++;
	}  
	std::cout << "" << std::endl;


	int size3 = serverconfig->getLocationConfig("/home.html").getMethods().size();
	i = 0;
	std::cout << COLOR_BLUE		<< "LOCATION 1" << COLOR_RESET	<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Path:\t\t\t" 			<< serverconfig->getLocationConfig("/img").getPath() 				<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Redirection:\t\t" 		<< serverconfig->getLocationConfig("/img").getRedirect() 			<< std::endl;
	std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "DirectoryListing:\t" 	<< serverconfig->getLocationConfig("/img").getDirectoryListing() 	<< std::endl;
	while (i < size3)
	{
		std::cout << COLOR_RED 		<< "│ " 		<< COLOR_RESET  << "Methods:\t\t" << serverconfig->getLocationConfig("/img").getMethods().at(i) << std::endl;
		i++;
	}
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
 }

