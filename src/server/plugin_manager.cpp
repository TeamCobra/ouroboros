#include <server/plugin_manager.h>
#include <server/plugin.h>
#include <dlfcn.h>
#include <iostream>

using namespace ouroboros;

plugin_manager::plugin_manager(ouroboros_server& aServer)
:mServer(aServer), mDirectory("./plugin")
{}

plugin_manager::plugin_manager(const std::string& aDirectory, ouroboros_server& aServer)
:mServer(aServer), mDirectory(aDirectory)
{}

plugin_manager::~plugin_manager()
{
	for (std::map<std::string, void*>::iterator itr = mPlugins.begin(); itr != mPlugins.end(); itr++)
	{
		unload(itr->first);
	}
	
}

bool plugin_manager::unload(const std::string& aPath)
{
	if (mPlugins.count(aPath))
	{
		dlclose(mPlugins[aPath]);
		return true;
	}
	return false;
}

bool plugin_manager::load(const std::string& aPath)
{
	typedef void* library_t;
	std::string fullPath(mDirectory + "/" + aPath);
	
	library_t lib = dlopen(fullPath.c_str(), RTLD_NOW);
	
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
	
	mPlugins[fullPath] = lib;
	return plugin(mServer);
}
