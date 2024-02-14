//no license available
//ÜreTech Engine Network System header file

#ifndef network_h
#define network_h
#include<WinSock2.h>
#include <WS2tcpip.h>
#include<string>

#include"../utils/Array.hpp"

namespace UreTechEngine {
	class networkSystem {
	public:
		struct clientData {
			sockaddr_in clientAddr;
			int sock;
		};

		static networkSystem* c_NetInst;
		static networkSystem* getNetworkSystem();

		bool invalidIP = true;

		void startServer();
		void connectToServer();
		void setToConnectIPAddr(std::string _ip,std::string _port);
		void disconnectToServer();
		void stopServer();
		void connectionRequest();
		void sendRecvToServer();
		void sendRecvToClient();
	private:
		size_t gamePageDataSize;
		char* gamePagePtr = nullptr;
		int sock,newsockfd;
		UreTechEngine::Array clientSocks;
	
		//int port=33660;
		int port = 80;
		sockaddr_in serv_addr, cli_addr;
		socklen_t clilen;
		networkSystem();
		~networkSystem();
	};
}
#endif // !network_h
