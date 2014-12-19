#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <slre/slre.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <data/base.hpp>
#include <data/data_store.hpp>
#include <device_tree.hpp>
#include <server/rest_handlers.h>

using namespace ouroboros;

enum mg_result handle_uri(struct mg_connection *conn, const char* uri)
{
	if (get_REST_call_type(uri) != REST_call_type::NONE)
	{
		std::string output;

		switch (get_REST_call_type(uri))
		{
			case REST_call_type::NAME:
				handle_name_REST(conn, uri);
				break;
				
			case REST_call_type::GROUP:
				handle_group_REST(conn, uri);
				break;
			
			case REST_call_type::CUSTOM:
				handle_custom_REST(conn, uri);
				break;
			
			default:
				return MG_FALSE; //Something really bad just took place... We got a REST call type that wasn't NONE but we didn't recognize!
		}
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
