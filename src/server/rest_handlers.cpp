#include <string>
#include "rest.h"
#include "rest_handlers.h"
#include <utility>

namespace ouroboros
{
	void handle_name_REST(const std::string& aURI)
	{
		std::pair<std::string, std::string> group_name = extract_group_name(aURI.c_str());
		//Determine type of REST Request Types
		auto type = get_HTTP_request_type(aURI);
	}

	void handle_group_REST(const std::string& aURI)
	{
		std::string group = extract_group(aURI.c_str());
	}

	void handle_custom_REST(const std::string& aURI)
	{
		//FIXME Implement this somehow
	}
}