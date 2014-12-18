#include <string>
#include "rest.h"
#include "rest_handlers.h"
#include <utility>

#include <cstring>

#include <data/base.hpp>
#include <server/device_tree.hpp>
#include <data/data_store.hpp>
#include <data/JSON.h>
#include <mongoose/mongoose.h>

namespace ouroboros
{
	device_tree<var_field> &tree = device_tree<var_field>::get_device_tree();
	data_store<var_field> &store = tree.get_data_store();
	
	namespace detail
	{
		std::string bad_JSON()
		{
			return std::string("{ \"status\" : \"Bad JSON request.\"}");
		}
		
		std::string good_JSON()
		{
			return std::string("{ \"status\" : \"OK.\"}");
		}
	}
	
	void handle_name_REST(struct mg_connection *conn, const std::string& aURI)
	{
		std::pair<std::string, std::string> group_name =
			extract_group_name(aURI.c_str());
		//Determine type of REST Request Types
		auto type = get_HTTP_request_type(conn->request_method);
		
		//get reference to named thing
		var_field *named = store.get(group_name.first, group_name.second);
		
		std::string sjson;
		if (named)
		{
			switch (type)
			{
				case HTTP_request_type::PUT:	
				{	
					std::string data(conn->content, conn->content_len);
					JSON json(data);
					if (named->setJSON(json))
					{
						sjson = detail::good_JSON();
					}
					else
					{
						sjson = detail::bad_JSON();
					}
				}
					break;
				
				case HTTP_request_type::GET:
					//Send JSON describing named item
					sjson = named->getJSON();
					break;
				
				default:
					sjson = detail::bad_JSON();
			}
		}
		else
		{
			sjson = detail::bad_JSON();
		}
		
		mg_send_data(conn, sjson.c_str(), sjson.length());
	}

	void handle_group_REST(struct mg_connection *conn, const std::string& aURI)
	{
		std::string sgroup = extract_group(aURI.c_str());
		
		auto type = get_HTTP_request_type(conn->request_method);
		
		//get reference to named thing
		group<var_field> *pgroup = store.get(sgroup);
		
		std::string sjson;
		if (pgroup)
		{
			switch (type)
			{
				case HTTP_request_type::GET:
					//Send JSON describing named item
					sjson = pgroup->getJSON();
					break;
				
				default:
					sjson = detail::bad_JSON();
			}
		}
		else
		{
			sjson = detail::bad_JSON();
		}
		
		mg_send_data(conn, sjson.c_str(), sjson.length());
	}

	void handle_custom_REST(struct mg_connection *conn, const std::string& aURI)
	{
		//TODO Implement this somehow
	}
}
