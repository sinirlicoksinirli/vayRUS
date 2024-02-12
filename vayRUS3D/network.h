//no license available
//ÜreTech Engine Network System header file

#ifndef network_h
#define network_h
#include<WinSock2.h>
#include <WS2tcpip.h>

namespace UreTechEngine {
	class networkSystem {
	public:
		static networkSystem* c_NetInst;
		static networkSystem* getNetworkSystem();
		void startServer();
		void connectToServer();
	private:
		int sock, newsockfd;
		int port=33660;
		struct sockaddr_in serv_addr, cli_addr;
		socklen_t clilen;
		networkSystem();
		~networkSystem();
	};
}
#endif // !network_h
