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


}

UreTechEngine::networkSystem::networkSystem()
{
}

