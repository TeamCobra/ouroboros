#include "../ouroboros_server.h"
#include "../callback.h"
#include "test.h"
#include <server/plugin.h>
#include <iostream>

using namespace ouroboros;
using namespace std;

void callback(const std::string& aGroup, const std::string& aField)
{
	cout << "we got a callback!!!" << endl;
}



extern "C" bool plugin_entry(ouroboros_server& aServer)
{
	cout << "Initializing plugin..." << endl;

	aServer.register_callback("", "a_number", ::callback);

	cout << "Done initializing." << endl;
	return true;
}

