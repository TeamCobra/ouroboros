#include <ouroboros/callback_manager.h>
#include <ouroboros/rest.h>
#include <ouroboros/data/misc.h>

#include <sstream>
#include <cstdlib>

namespace ouroboros
{
	static const std::string rand_string("0123456789");

	callback_manager::callback_manager()
	{}

	std::string callback_manager::register_callback(
		const std::string& aFieldName)
	{
		std::string result = aFieldName;
		result += ":";
		result = detail::generate_random_string(result, rand_string, 1);

		while (mIdToCallbacks.count(result))
		{
			result = detail::generate_random_string(result, rand_string, 1);
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
