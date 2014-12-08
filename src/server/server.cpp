#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <slre/slre.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <data/base.hpp>
#include <data/data_store.hpp>
#include <device_tree.h>

using namespace ouroboros;

//TODO make a singleton for the device tree
data_store<var_field> device_tree = get_data_store();

enum mg_result handle_uri(struct mg_connection *conn, const char* uri)
{
	if (get_REST_call_type(uri) != REST_call_type::NONE)
	{
		std::string output;
		//Check type of REST API call
		switch (get_REST_call_type(uri))
		{
		case REST_call_type::NAME:
		{
			std::pair<std::string, std::string> group_name = extract_group_name(uri);
			//Determine type of REST Request Types
		}
			
			break;
		case REST_call_type::GROUP:
		{
			std::string group = extract_group(uri);
			//Determine type of REST Request Types
		}
			break;
		case REST_call_type::CUSTOM:
		{
			//FIXME Implement this somehow
			break;
		}
		}
		
		
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
    	
	    return MG_TRUE;
	}
	return MG_FALSE;
}

int event_handler(struct mg_connection *conn, enum mg_event ev)
{
	if (ev == MG_AUTH)
	{
		return MG_TRUE;
	}
	else if (ev == MG_REQUEST)
	{
		return handle_uri(conn, conn->uri);
	}
	else
	{
		return MG_FALSE;
	}
}

int main(void) {
	struct mg_server *server = mg_create_server(NULL, event_handler);
	mg_set_option(server, "document_root", ".");      // Serve current directory
	mg_set_option(server, "listening_port", "8080");  // Open port 8080

	for (;;) {
    	mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
    }
	mg_destroy_server(&server);

	return 0;
}
