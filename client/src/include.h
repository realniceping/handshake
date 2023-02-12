#ifndef INCLUDE_H
#define INCLUDE_H

#include<iostream>
#include"winsock2.h"
#include<ws2tcpip.h>

#define WINDOWS
#ifdef WINDOWS
#pragma comment(lib, "ws2_32.lib");
#endif

//project configuration
#define DEBUG
#ifdef DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 
#endif
//end project configuration

#endif