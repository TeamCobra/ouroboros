#include <string>
#include "rest.h"
#include "rest_handlers.h"
#include <utility>

#include <cstring>

#include <data/base.hpp>
#include <server/device_tree.h>
#include <data/data_store.hpp>

#include <mongoose/mongoose.h>

namespace ouroboros
{
	//TODO make a singleton for the device tree
	data_store<var_field> device_tree = get_data_store();
	
	void handle_name_REST(struct mg_connection *conn, const std::string& aURI)
	{
		std::pair<std::string, std::string> group_name = extract_group_name(aURI.c_str());
		//Determine type of REST Request Types
		auto type = get_HTTP_request_type(aURI);
		
		char data[256];
	   	base_string* bstring = reinterpret_cast<base_string*>(device_tree.get("main", "root"));

		data[0] = '\0';
    	strcat(data, "<html><head><title>Hello world!</title></head><body>");
	    time_t current_time = time(NULL);
	    strcat(data, ctime(&current_time));
	    strcat(data, "</br>");
		bstring->setString("TESTING");
	   	strcat(data, device_tree.get("main", "root")->getValue().c_str());
    	strcat(data, "</body></html>");

    	mg_send_data(conn, data, strlen(data));
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