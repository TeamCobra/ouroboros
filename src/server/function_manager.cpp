#include <server/function_manager.h>

#include <vector>
#include <string>

namespace ouroboros
{
	
	function_manager::function_manager()
	{}
	
	bool function_manager::register_function(const std::string& aFunctionName, function_f aResponse)
	{
		mFunctionCallbacks[aFunctionName].push_back(aResponse);
		
		return true;
	}
	
	void function_manager::execute_function(const std::string& aFunctionName, const std::vector<std::string>& aParameters)
	{
		if (mFunctionCallbacks.count(aFunctionName))
		{
			typedef std::vector<function_f>::const_iterator iter;
			std::vector<function_f>& vec = mFunctionCallbacks[aFunctionName];
			for (iter itr = vec.begin(); itr != vec.end(); ++itr)
			{
				(*itr)(aParameters);
			}
		}
	}
}
