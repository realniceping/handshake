#include"include.h"
#include"clientcfg.h"

int main(){

    //init wsa
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        std::cout << "lib not init" << std::endl;
        
        return EXIT_FAILURE;
    }
    //end init

    //init tcp socket 
    SOCKET clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSocket == INVALID_SOCKET){
        std::cout << "invalid socket" << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }
    LOG("socket created");
    //socket inited

    //connect to server socket
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(SERVER_PORT);
    int con_status = connect(clientSocket, (SOCKADDR*)&server_addr,sizeof(server_addr));
    if(con_status == SOCKET_ERROR){
        std::cout << "connection fail" << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    } 
    LOG("con status = ");
    LOG(con_status);
    LOG("Connection success");

    if(clientSocket == INVALID_SOCKET){
        std::cout << "bad socket" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
    }

    char* message = "Isaac Newton";
    int send_code = send(clientSocket, message, (int)strlen(message), 0);
    if(send_code > 0){
        std::cout << "bytes recived " << send_code << std::endl;
    }
    if(send_code == 0){
        std::cout << "connection closed with exit code = 0" << std::endl;
    }
    if(send_code < 0){
        std::cout << "data recv fail "<< WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    closesocket(clientSocket);
    WSACleanup();
    return EXIT_SUCCESS;
}

