#ifndef _OUROBOROS_PLUGIN_MANAGER_H_
#define _OUROBOROS_PLUGIN_MANAGER_H_

#include <server/ouroboros_server.h>

namespace ouroboros
{
	class plugin_manager
	{
	public:
		plugin_manager(ouroboros_server& aServer);
		bool load(const std::string& aPath);
	private:
		ouroboros_server& mServer;
	};
}

#endif//_OUROBOROS_PLUGIN_MANAGER_H_
