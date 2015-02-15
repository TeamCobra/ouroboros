#include <server/plugin_manager.h>
#include <server/plugin.h>
#include <dlfcn.h>
#include <iostream>

using namespace ouroboros;


plugin_manager::plugin_manager(ouroboros_server& aServer)
:mServer(aServer)
{}

bool plugin_manager::load(const std::string& aPath)
{
	typedef void* library_t;
	library_t lib = dlopen(aPath.c_str(), RTLD_NOW);
	
	const char *err = dlerror();
	if (err)
	{
		std::cout << err << std::endl;
		return false;
	}

	plugin_entry_function plugin =
		reinterpret_cast<plugin_entry_function>(dlsym(lib, "plugin_entry"));
	
	
	if ((err = dlerror()))
	{
		std::cout << err << std::endl;
		return false;
	}
	else
	{
		return plugin(mServer);
	}
}
