// Для инициализации сокета на строне сервера необходимо
// 1) Загрузить библиотеку
// 2) проинициализировать сокет 
// 3) забиндить сокет
// 4) начать листенить сокет 
// 5)
// 6)
// 7)

#include"serverconfig.h"
#include"include.h"
int main(){

    //lib connecting
    WSADATA WSAData;
    WORD wsVersion = MAKEWORD(2, 2);
    if(WSAStartup(wsVersion, &WSAData) != 0){
        std::cout << "bad lib init" << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }
    LOG("lib inited");
    LOG(WSAData.szSystemStatus);
    //end lib connecting  

    //socket initialization      
                                //AF_INET - Семейство IPV4
                                //SOCK_STREAM - тип сокета необходимый для TCP сокета
                                //IPPROTO_TCP - протокол TCP
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // initilizing tcp socket
    if(serverSocket == INVALID_SOCKET){
        std::cout << "socket() executed with error" << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }
    LOG("SOCKET CREATED SUCCESFULLY!");
    //socket initiazed

    //binding socket 
    sockaddr_in service; 
    service.sin_family = AF_INET; //ipv4 family
    service.sin_addr.s_addr = inet_addr("127.0.0.1"); // loopback address 
    service.sin_port = htons(PORT); //predefined const post - recomend user above 1023

    int sockBind = bind(serverSocket, (SOCKADDR * )&service, sizeof(service));
    if(sockBind == SOCKET_ERROR){
        std::cout << "erorr - socket unbinded" << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }
    LOG("socket binded");
    //socket binded

    //start setting socket listening 
    int sockListen = listen(serverSocket, 1); //поставили serversocket слушать на одно максимальное подключение 
    if(sockListen == SOCKET_ERROR){
        std::cout << "function socket listen - error" << std::endl;
        std::cout << WSAGetLastError() << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    } 
    LOG("SOCKET START LISTENING ");
    //socket set to listened

    std::cout << "try to find socket with " << PORT << " port in netstat -a!" << std::endl;
    std::system("pause");
    closesocket(serverSocket);
    WSACleanup();
    std::system("pause");
    return EXIT_SUCCESS;
}
