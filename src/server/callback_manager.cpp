#include <server/rest.h>
#include "callback_manager.h"
#include <sstream>
#include <cstdlib>

namespace ouroboros
{
	static const std::string rand_string("0123456789");
	
	callback_manager::callback_manager()
	{}
	
	static std::string generate_random_string(const std::string& aBase, std::size_t aNAppend)
	{
		std::string result(aBase);
		for (std::size_t i = 0; i < aNAppend; ++i)
		{
			result += rand_string[rand() % rand_string.length()];
		}
		return result;
	}
	
	std::string callback_manager::register_callback(const std::string& aFieldName)
	{
		std::string result = aFieldName;
		result += ":";
		result = generate_random_string(result, 1);
		
		while (mIdToCallbacks.count(result))
		{
			result = generate_random_string(result, 1);
		}
		
		mIdToCallbacks[result] = aFieldName;
		return result;
	}
	
	std::string callback_manager::unregister_callback(const std::string& aID)
	{
		std::string result;
		if (mIdToCallbacks.count(aID))
		{
			result = mIdToCallbacks[aID];
		}
		mIdToCallbacks.erase(aID);
		return result;
	}
}
