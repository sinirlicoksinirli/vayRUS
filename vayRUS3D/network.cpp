#include "network.h"
#include<WinSock2.h>
#include"errOut.h"
#include<string>

namespace UreTechEngine {
    class EngineERROR;
}

UreTechEngine::networkSystem* UreTechEngine::networkSystem::c_NetInst = nullptr;

UreTechEngine::networkSystem* UreTechEngine::networkSystem::getNetworkSystem()
{
    if (c_NetInst == nullptr) {
        c_NetInst = new networkSystem();
        return c_NetInst;
    }
    else {
        return c_NetInst;
    }
    return nullptr;
}

void UreTechEngine::networkSystem::startServer()
{
    WSADATA wsaData;
    int result;
    // Winsock baþlatma
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to WSAStartup! ERROR CODE:") + std::to_string(result), EngineERROR::ERROR_FATAL);

    }

    sock=socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to open socket! ERROR CODE:")+ std::to_string(sock), EngineERROR::ERROR_FATAL);
    }
    EngineERROR::consoleError("Socket: Server Socket Started!", EngineERROR::INFO_NORMAL);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // automatically be filled with current host's IP address
    serv_addr.sin_port = htons(port);
    int bind_Err;
    if (bind_Err = bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to bind! ERROR CODE:") + std::to_string(bind_Err), EngineERROR::ERROR_FATAL);
    }
    listen(sock, 5);
    clilen = sizeof(cli_addr);

    char buffer[256];

    newsockfd = accept(sock,
        (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd < 0) {
        EngineERROR::consoleError(std::string("(Network): Error conn!"), EngineERROR::ERROR_FATAL);
    }
        

    printf("server: got connection from %s port %d\n",
        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));


    // This send() function sends the 13 bytes of the string to the new socket
    send(newsockfd, "Hello, world!\n", 13, 0);
    int n;

    n = recv(newsockfd, buffer, 255,0);
    if (n < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed read socket"), EngineERROR::WARN_CAN_CAUSE_ERROR);
    }

    EngineERROR::consoleError(std::string("(Network Socket): Read to socket:") + std::string(buffer), EngineERROR::INFO_NORMAL);

    closesocket(newsockfd);
    closesocket(sock);

}

void UreTechEngine::networkSystem::connectToServer()
{
    char buffer[256];
    int n;

    WSADATA wsaData;
    int result;
    // Winsock baþlatma
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to WSAStartup! ERROR CODE:") + std::to_string(result), EngineERROR::ERROR_FATAL);

    }

    if (sock < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to open socket! ERROR CODE:") + std::to_string(sock), EngineERROR::ERROR_FATAL);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
 }
    EngineERROR::consoleError("Socket: Client Socket Started!", EngineERROR::INFO_NORMAL);

    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Can not connect to server!"), EngineERROR::ERROR_FATAL);
    }
    EngineERROR::consoleError("(DEBUG): enter message", EngineERROR::INFO_NORMAL);
    fgets(buffer, 255, stdin);

    n = send(sock, buffer, strlen(buffer),0);
    if (n < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Can not write to server!"), EngineERROR::ERROR_FATAL);
    }
        

    n = recv(sock, buffer, 255,0);
    if (n < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Can not read from server!"), EngineERROR::ERROR_FATAL);
    }
       
    printf("%s\n", buffer);

    closesocket(sock);
}

UreTechEngine::networkSystem::networkSystem()
{
}

