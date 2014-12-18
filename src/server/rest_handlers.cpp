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
	device_tree<var_field> &tree = device_tree<var_field>::get_device_tree();
	data_store<var_field> &store = tree.get_data_store();
	
	namespace detail
	{
		std::string bad_JSON()
		{
			return std::string("{ \"description\" : \"Bad JSON request.\"}");
		}
		
		std::string good_JSON()
		{
			return std::string("{ \"description\" : \"OK.\"}");
		}
	}
	
	void handle_name_REST(struct mg_connection *conn, const std::string& aURI)
	{
		std::pair<std::string, std::string> group_name =
			extract_group_name(aURI.c_str());
		//Determine type of REST Request Types
		auto type = get_HTTP_request_type(conn->request_method); //TODO This looks like I am trying to use typing to select functionality. This is a candidate for using templates and SFINAE.
		
		//get reference to named thing
		var_field *named = store.get(group_name.first, group_name.second);
		
		std::string json;
		if (named)
		{
			switch (type)
			{
				case HTTP_request_type::PUT:	
					//TODO Read PUT information to update named item
					json = detail::good_JSON();
					break;
				
				case HTTP_request_type::GET:
					//Send JSON describing named item
					json = named->getValue();
					break;
				
				default:
					json = detail::bad_JSON();
				
			}
		
		}
		else
		{
			json = detail::bad_JSON();
		}
		
		mg_send_data(conn, json.c_str(), json.length());
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