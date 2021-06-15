#include <string>
#include <iostream>
#ifdef __unix__         
	#include <unistd.h>
	#include <stdlib.h>
	#include "nfd.h"
	

#elif defined(_WIN32) || defined(WIN32) 

	#define OS_Windows
	#include <windows.h>
#endif
	std::string DialogoDeAberturaDeArquivo();
