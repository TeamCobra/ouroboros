#ifndef _OUROBOROS_FUNCTION_MANAGER_H_
#define _OUROBOROS_FUNCTION_MANAGER_H_

#include <server/callback.hpp>

#include <vector>
#include <string>
#include <map>

namespace ouroboros
{
	class function_manager
	{
	public:
		function_manager();
		typedef void (*function_f)(const std::vector<std::string>& aArguments);
		
		/**	Registers a response function for the specified function call.
		 *
		 *	@param [in] aFunctionName Name of the function to register.
		 *	@param [in] aResponse Callback functor that is called as
		 *		void(std::vector<std::string>) function.
		 *	@returns True upon success, false otherwise.
		 */
		bool register_function(const std::string& aFunctionName, function_f aResponse);
		
		/**	Executes a response function for the specified function call.
		 *
		 *	@param [in] aFunctionName Name of the function to call.
		 *	@param [in] aParameters Parameters as strings in a vector.
		 */
		void execute_function(const std::string& aFunctionName, const std::vector<std::string>& aParameters);
		
	private:
		function_manager(const function_manager&);
		std::map<std::string, std::vector<function_f> > mFunctionCallbacks;
	};
}

#endif/*_OUROBOROS_FUNCTION_MANAGER_H_*/
