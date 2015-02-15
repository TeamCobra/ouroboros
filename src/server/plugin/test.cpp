#include "../ouroboros_server.h"
#include "test.h"
#include <server/plugin.h>
#include <iostream>

using namespace ouroboros;
using namespace std;

extern "C" bool plugin_entry(ouroboros_server& aServer)
{
	cout << "Initializing plugin..." << endl;
	cout << aServer.get("server")->getJSON() << endl;
	cout << "Done initializing." << endl;
	return true;
}

