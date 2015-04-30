#include <server/function_manager.h>

#include <vector>
#include <string>

namespace ouroboros
{
	
	function_manager::function_manager()
	{}
	
	bool function_manager::register_function(const std::string& aFunctionName, function_f aResponse)
	{
		return false;
	}
	
	void function_manager::execute_function(const std::string& aFunctionName, const std::vector<std::string>& aParameters)
	{
		
	}

}
