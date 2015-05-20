#include <ouroboros/ouroboros_server.h>
#include <ouroboros/plugin_manager.h>
#include <ouroboros/plugin.h>

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <dlfcn.h>

using namespace std;
using namespace ouroboros;

volatile std::sig_atomic_t run = 0;
void handler(int)
{
	run = 0;
}

int main()
{
	cout << "Starting Ouroboros...\n";

	std::string plugin_directory("plugin");
	ouroboros_server s(8080);
	plugin_manager plugin_manager(s);

	cout << "\tPlugins loaded : " <<
		plugin_manager.load_directory(plugin_directory) << endl;
	signal(SIGINT, handler);

	run = 1;
	while (run)
	{
		s.run();
	}

	cout << "Exiting Ouroboros..." << endl;
	return 0;
}
