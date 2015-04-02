#include "ouroboros_server.h"
#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include "plugin.h"
#include <server/plugin_manager.h>
#include <csignal>

using namespace std;
using namespace ouroboros;

volatile std::sig_atomic_t run = 0;
void handler(int)
{
	run = 0;
}

int main()
{
	std::string plugin_directory("plugin");
	ouroboros_server s;
	plugin_manager plugin_manager(s);
	
	cout << "Loaded plugin? : " << plugin_manager.load_directory(plugin_directory) << endl;
	signal(SIGINT, handler);
	
	run = 1;
	while (run)
	{
		s.run();
	}

	cout << "Exiting program..." << endl;
	return 0;
}
