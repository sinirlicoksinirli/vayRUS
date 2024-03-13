#include "defaultNetworkStructs.h"

void func_rep_Test(char* input) {
	func_rep_Test_input_struct* inputData = (func_rep_Test_input_struct*)input;
	EngineERROR::consoleError("(Network Replication)[DEBUG]: Now replicating...", EngineERROR::INFO_NORMAL);
	EngineERROR::consoleError("(Network Replication)[DEBUG]:" + std::string(inputData->test), EngineERROR::INFO_NORMAL);
	EngineERROR::consoleError("(Network Replication)[DEBUG]:" + std::to_string(inputData->test_val0), EngineERROR::INFO_NORMAL);
}

networkReplicationStruct::networkReplicationStruct()
{
	networkSystem* _netSys = networkSystem::getNetworkSystem();

	_netSys->rep_func_map["func_rep_Test"] = func_rep_Test;
	_netSys->rep_func_inputs["func_rep_Test"] = &func_test_input;

	memset(func_notify, 0, sizeof(func_notify));
	memset(func_notify_to_ent, 0, sizeof(func_notify_to_ent));
}

void networkReplicationStruct::run_noticed_funcs()
{
	networkSystem* _netSys = networkSystem::getNetworkSystem();
	for (int i = 0; i < network_max_func_per_tick; i++) {
		if (_netSys->rep_func_map.find(func_notify[i]) != _netSys->rep_func_map.end()) {
			_netSys->rep_func_map[func_notify[i]]((char*)_netSys->rep_func_inputs[func_notify[i]]);
			EngineERROR::consoleError("(Network Replication): Replicating function:" + std::string(func_notify[i]), EngineERROR::ERROR_NORMAL);
		}
		else {
			EngineERROR::consoleError("(Network Replication): Can not find this replicate function:" + std::string(func_notify[i]), EngineERROR::ERROR_NORMAL);
		}
	}
}
