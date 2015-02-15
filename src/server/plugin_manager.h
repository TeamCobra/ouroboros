#ifndef _OUROBOROS_PLUGIN_MANAGER_H_
#define _OUROBOROS_PLUGIN_MANAGER_H_

#include <server/ouroboros_server.h>
#include <map>
#include <string>

namespace ouroboros
{
	class plugin_manager
	{
	public:
		plugin_manager(ouroboros_server& aServer);
		plugin_manager(const std::string& aDirectory, ouroboros_server& aServer);
		~plugin_manager();
		bool load(const std::string& aPath);
		bool unload(const std::string& aPath);
		
	private:
		ouroboros_server& mServer;
		std::map<std::string, void*> mPlugins;
		std::string mDirectory;
	};
}

#endif//_OUROBOROS_PLUGIN_MANAGER_H_
