#include "ouroboros_server.h"
#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include "plugin.h"
#include <server/plugin_manager.h>

using namespace std;
using namespace ouroboros;

int main()
{
	ouroboros_server s;
	s.start();

	plugin_manager plugin_manager(s);
	cout << "Loaded plugin? : " << plugin_manager.load("libtest.so") << endl;
//	sleep(1000);
	s.stop();
	return 0;
}
