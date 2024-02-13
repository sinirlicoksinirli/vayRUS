#include "network.h"
#include<WinSock2.h>
#include"../UreTechEngine/utils/errOut.h"
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

    // Non-blocking mod ayarlanýyor(GPT kodu bu) // düzeltilmeli bloklamýyo ama accept edemiyor
    u_long mode = 1;
    if (ioctlsocket(sock, FIONBIO, &mode) == SOCKET_ERROR) {
        EngineERROR::consoleError(std::string("(Network Socket): Non blocking socket error!") + std::to_string(sock), EngineERROR::ERROR_FATAL);
    }

    EngineERROR::consoleError("Socket: Server Socket Started!", EngineERROR::INFO_NORMAL);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // automatically be filled with current host's IP address
    serv_addr.sin_port = htons(port);
    int bind_Err;
    if (bind_Err = bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to bind! ERROR CODE:") + std::to_string(bind_Err), EngineERROR::ERROR_FATAL);
    }

    if (listen(sock, 5)==SOCKET_ERROR) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to listen!"), EngineERROR::ERROR_FATAL);
    }
    clilen = sizeof(cli_addr);

    char buffer[256];

    newsockfd = accept(sock, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd == INVALID_SOCKET) {
        int errorCode = WSAGetLastError();
        if (errorCode != WSAEWOULDBLOCK) {
            EngineERROR::consoleError(std::string("(Network): Client can not connect!") + std::to_string(errorCode), EngineERROR::ERROR_NORMAL);
        }
    }
    else {
        EngineERROR::consoleError("aaaaaaa", EngineERROR::INFO_NORMAL);

        printf("server: got connection from %s port %d\n",
            inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));


        // This send() function sends the 13 bytes of the string to the new socket
        send(newsockfd, "OK 200", 13, 0);
        int n;

        n = recv(newsockfd, buffer, 255, 0);
        if (n < 0) {
            EngineERROR::consoleError(std::string("(Network Socket): Failed read socket"), EngineERROR::WARN_CAN_CAUSE_ERROR);
        }

        EngineERROR::consoleError(std::string("(Network Socket): Read to socket:") + std::string(buffer), EngineERROR::INFO_NORMAL);

        stopServer();
    }  
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

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        EngineERROR::consoleError(std::string("(Network Socket): Failed to open socket! ERROR CODE:") + std::to_string(sock), EngineERROR::ERROR_FATAL);
    }

    EngineERROR::consoleError("Socket: Client Socket Started!", EngineERROR::INFO_NORMAL);

    if (invalidIP) {
        EngineERROR::consoleError("(Network Socket): Server is not available!",EngineERROR::ERROR_NORMAL);
    }
    else {
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            EngineERROR::consoleError(std::string("(Network Socket): Can not connect to server!"), EngineERROR::ERROR_NORMAL);
        }
        EngineERROR::consoleError("(DEBUG): enter message", EngineERROR::INFO_NORMAL);
        fgets(buffer, 255, stdin);

        n = send(sock, buffer, strlen(buffer), 0);
        if (n < 0) {
            EngineERROR::consoleError(std::string("(Network Socket): Can not write to server!"), EngineERROR::ERROR_NORMAL);
        }


        n = recv(sock, buffer, 255, 0);
        if (n < 0) {
            EngineERROR::consoleError(std::string("(Network Socket): Can not read from server!"), EngineERROR::ERROR_NORMAL);
        }

        printf("%s\n", buffer);
        disconnectToServer();
    }
}

void UreTechEngine::networkSystem::setToConnectIPAddr(std::string _ip, std::string _port)
{
    serv_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, _ip.c_str(), &serv_addr.sin_addr) <= 0) { 
        EngineERROR::consoleError(std::string("(Network Socket): Invalid ip addres!"), EngineERROR::ERROR_NORMAL);
        invalidIP = true;
    }
    else {
        invalidIP = false;
    }
    int portNo;
    sscanf(_port.c_str(), "%i", &portNo);
    serv_addr.sin_port = htons(portNo);
}

void UreTechEngine::networkSystem::disconnectToServer()
{
    closesocket(sock);
}

void UreTechEngine::networkSystem::stopServer()
{
    closesocket(newsockfd);
    closesocket(sock);
}

UreTechEngine::networkSystem::networkSystem()
{
}

