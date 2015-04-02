#include <server/plugin_manager.h>
#include <server/plugin.h>
#include <dlfcn.h>
#include <dirent.h>
#include <iostream>

using namespace ouroboros;

plugin_manager::plugin_manager(ouroboros_server& aServer)
:mServer(aServer)
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
	std::string fullPath(aPath);
	
	library_t lib = dlopen(fullPath.c_str(), RTLD_NOW);
	
	//FIXME determine what to do with diagnostics
	const char *err = dlerror();
	if (err)
	{
		std::cerr << err << std::endl;
		return false;
	}

	//This is a hackish way to ward off undefined behavior caused by dlsym.
	//In short, POSIX requires conversions between object pointers and
	//function pointers to be possible, while the C and C++ ISO standards
	//do not. As a result, a simple cast is insuficcient. On the plus side,
	//newer POSIX standard require that this conversion be supported in order
	//for a system to be POSIX compliant, so any systems that can use dlsym
	//support this conversion.
	plugin_entry_function plugin;
	*(void **) (&plugin) = dlsym(lib, "plugin_entry");	
	if ((err = dlerror()))
	{
		std::cout << err << std::endl;
		return false;
	}
	
	mPlugins[fullPath] = lib;
	return plugin(mServer);
}

#include <errno.h>

static std::vector<std::string> list_files(const std::string& aDir)
{
	std::vector<std::string> results;

	char abs_path[PATH_MAX];
	realpath(aDir.c_str(), abs_path);
	
	std::string directory(abs_path);
	directory += '/';
	
	DIR *d = opendir(abs_path);
	
	if (d)
	{
		dirent *dir;
		while ((dir = readdir(d)) != NULL)
		{
			results.push_back(realpath((directory + dir->d_name).c_str(), abs_path));
		}

		closedir(d);
	}
	
	return results;
}

std::size_t plugin_manager::load_directory(const std::string& aDirectory)
{
	std::size_t number_loaded = 0;
	
	std::vector<std::string> files(list_files(aDirectory));
	
	if (!files.empty())
	{
		for (std::size_t i = 0; i < files.size(); ++i)
		{
			number_loaded += load(files[i]);
		}
	}
	
	return number_loaded;
}

