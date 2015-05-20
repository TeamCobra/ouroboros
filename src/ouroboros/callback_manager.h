#ifndef _OUROBOROS_CALLBACK_MANAGER_H_
#define _OUROBOROS_CALLBACK_MANAGER_H_

#include <ouroboros/rest.h>
#include <map>

namespace ouroboros
{
	class callback_manager
	{
	public:
		callback_manager();

		std::string register_callback(const std::string& aFieldName);
		std::string unregister_callback(const std::string& aID);

	private:
		std::map<std::string, std::string > mIdToCallbacks;
	};
}

#endif//_OUROBOROS_CALLBACK_MANAGER_H_
