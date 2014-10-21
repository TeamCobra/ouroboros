#include "mongoose.h"
#include <string.h>

int event_handler(struct mg_connection *conn, enum mg_event ev)
{
	if (ev == MG_AUTH)
	{
		return MG_TRUE;
	}
	else if (ev == MG_REQUEST && !strcmp(conn->uri, "/hello"))
	{
		mg_printf_data(conn, "%s", "Hello World!!!");
		return MG_TRUE;
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
