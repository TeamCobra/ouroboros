#include <string>
#include "rest.h"
#include "rest_handlers.h"
#include <utility>

#include <cstring>

#include <data/base.hpp>
#include <server/device_tree.hpp>
#include <data/data_store.hpp>

#include <mongoose/mongoose.h>

//TODO make this work by using templates instead of different functions for different types(!)

namespace ouroboros
{
	//TODO make a singleton for the device tree
	device_tree<var_field> &tree = device_tree<var_field>::get_device_tree();
	data_store<var_field> &store = tree.get_data_store();
	
	void handle_name_REST(struct mg_connection *conn, const std::string& aURI)
	{
		std::pair<std::string, std::string> group_name =
			extract_group_name(aURI.c_str());
		//Determine type of REST Request Types
		auto type = get_HTTP_request_type(aURI); //TODO This looks like I am trying to use typing to select functionality. This is a candidate for using templates and SFINAE.
		
		
	}

	void handle_group_REST(struct mg_connection *conn, const std::string& aURI)
	{
		std::string group = extract_group(aURI.c_str());
	}

	void handle_custom_REST(struct mg_connection *conn, const std::string& aURI)
	{
		//FIXME Implement this somehow
	}
}