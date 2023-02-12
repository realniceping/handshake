// Для инициализации сокета на строне сервера необходимо
// 1) Загрузить библиотеку - WSAStartup()
// 2) проинициализировать сокет - socket() 
// 3) забиндить сокет - bind()
// 4) начать листенить сокет - listen()
// 5) создать connection - accept(), connect()
// 6) Отправить или принять данные - recv(), send(), recvform(), sendto()
// 7) Дисконект - closesocket()

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
    int sockListen = listen(serverSocket, MAX_CONNECTIONS); //поставили serversocket слушать на n подключений см.конфигурацию
    if(sockListen == SOCKET_ERROR){
        std::cout << "function socket listen - error" << std::endl;
        std::cout << WSAGetLastError() << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    } 
    LOG("SOCKET START LISTENING ");
    //socket set to listened

    //socket try to accept connection
    SOCKET acceptSocket;
    std::cout << "whait client connection" << std::endl;
   
    acceptSocket = accept(serverSocket, NULL, NULL); // ожидает соеденения
    if(acceptSocket == INVALID_SOCKET){
        std::cout << "accepted failed" << std::endl;
        std::cout << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }
    //socket accepted connection

    std::cout << "client connectd" << std::endl;
    //после подключение клиента к серверу сокет дублируется, так что держать открытым сокет более не требуется
    if(CLOSE_SERVER_SOCKET_AFTER_CONNECTION){
        std::cout << "server socket not longer needed" << std::endl;
        closesocket(serverSocket);
    }
  

    //if connection accepted
    int status;
    char* reqbuff = new char[BUFFSIZE];
    do{
        status = recv(acceptSocket, reqbuff, BUFFSIZE, 0);
        if(status > 0){
            std::cout << "bytes reveived: " << status << std::endl;
            std::cout << "message: ";
            std::cout << reqbuff << std::endl;
            continue;
        }
        if(status == 0){
            std::cout << "connection closing with exit code = " << status << std::endl;
        }
        if(status < 0){
            std::cout << "fail to recv data" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            closesocket(acceptSocket);
            WSACleanup();
            return EXIT_FAILURE;
        }

    }while(status > 0); 
    //end 

    //разрыв соеденения 
    int disconnect = shutdown(acceptSocket, SD_SEND);
    if(disconnect == SOCKET_ERROR){
        std::cout << "shutdown failed with error" << std::endl;
        std::cout << WSAGetLastError() << std::endl;
        closesocket(acceptSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    //end



    std::cout << "try to find socket with " << PORT << " port in netstat -a!" << std::endl;
    std::system("pause");
    closesocket(serverSocket);
    WSACleanup();
    std::system("pause");
    return EXIT_SUCCESS;
}
 