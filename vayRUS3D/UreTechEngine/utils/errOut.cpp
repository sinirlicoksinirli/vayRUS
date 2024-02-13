#include "errOut.h"
#include <string>
#include <iostream>
#include<conio.h>
using namespace std;
namespace UreTechEngine {
	class EngineERROR;
}
void UreTechEngine::EngineERROR::consoleError(std::string _errMsg, t_error errTyp)
{
	switch (errTyp)
	{
	case UreTechEngine::EngineERROR::ERROR_ERROR:
		cout << "(?)UNKNOWN ERROR:" << _errMsg<<endl;
		break;
	case UreTechEngine::EngineERROR::ERROR_FATAL:
		cout << "(!)FATAL ERROR:" << _errMsg << endl;
		forceToExit();
		break;
	case UreTechEngine::EngineERROR::ERROR_NORMAL:
		cout << "(i)ERROR:" << _errMsg << endl;
		break;
	case UreTechEngine::EngineERROR::WARN_NORMAL:
		cout << "(i)WARN:" << _errMsg << endl;
		break;
	case UreTechEngine::EngineERROR::WARN_CAN_CAUSE_ERROR:
		cout << "(!)WARN:" << _errMsg << endl;
		break;
	case UreTechEngine::EngineERROR::INFO_NORMAL:
		cout << "(i)INFO:" << _errMsg << endl;
		break;
	default:
		cout << "UNKNOWN: an unknown error reported! chech your code." << endl;
		break;
	}
}

void UreTechEngine::EngineERROR::forceToExit()
{
	cout << "press esc to exit..." << endl;
	while (getch()!= 27) {}
	exit(-1);
}
