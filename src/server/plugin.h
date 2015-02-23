#ifndef _OUROBOROS_PLUGIN_H_
#define _OUROBOROS_PLUGIN_H_

#include <server/ouroboros_server.h>

namespace ouroboros
{
	typedef bool (*plugin_entry_function)(ouroboros_server& aServer);
	extern "C" bool plugin_entry(ouroboros_server& aServer);
}

#endif//_OUROBOROS_PLUGIN_H_
