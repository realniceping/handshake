#include<iostream>
#include"winsock2.h"
#include<ws2tcpip.h>

#define WINDOWS
#ifdef WINDOWS
#pragma comment(lib, "ws2_32.lib");
#endif

#define PORT 3030
int main(){
    SOCKET serverSocket, acceptSocket;
    WSADATA WSAData;
    int wsaErr;
    WORD wsVersion = MAKEWORD(2, 2);
    if(WSAStartup(wsVersion, &WSAData) != 0){
        std::cout << "bad lib init" << std::endl;
        return 1;
    }
    std::cout << "lib inited" << std::endl;
    std::cout << WSAData.szSystemStatus << std::endl;
    
    // std::system("pause");
    return 0;
}
