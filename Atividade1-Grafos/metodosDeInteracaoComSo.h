#pragma once
#include <iostream>
#ifdef __unix__         
#include <unistd.h>
#include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32) 

#define OS_Windows
#include <windows.h>
#endif


void LimparTela();
void Pause();
