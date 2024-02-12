//no license available
//ÜreTech Engine Network System header file

#ifndef network_h
#define network_h
#include<WinSock2.h>

namespace UreTechEngine {
	class networkSystem {
	public:
		static networkSystem* c_NetInst;
		static networkSystem* getNetworkSystem();
		void startServer();
	private:
		int sock;
		int port=33660;
		struct sockaddr_in serv_addr, cli_addr;
		networkSystem();
		~networkSystem();
	};
}
#endif // !network_h
