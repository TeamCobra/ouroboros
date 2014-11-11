#include "mongoose.h"
#include "slre.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool is_REST_URI(const char* aURI)
{
	const char * regex = "/group/([^/]+?)/name/([^/]+?)";
	int result = slre_match(regex, aURI, strlen(aURI), NULL, 0, 0);
	return (result >= 0);
}

void extract_group_name(const char* aURI, char *aGroupName, size_t groupLength, char *aName, size_t aNameLength)
{
	const char * regex = "/group/([^/]+?)/name/([^/]+?)";
	struct slre_cap match[2];
	//FIXME should we limit the size?
	int result = slre_match(regex, aURI, strlen(aURI), match, 2, 0);
	memcpy(aGroupName, match[0].ptr, match[0].len); //FIXME actually limit the size
	memcpy(aName, match[1].ptr, match[1].len); //FIXME actually limit the size
}

enum mg_result handle_uri(struct mg_connection *conn, const char* uri)
{
	if (is_REST_URI(uri))
	{
		char *data = malloc(256);

		data[0] = '\0';
    	strcat(data, "<html><head><title>Hello world!</title></head><body>");
	    time_t current_time = time(NULL);
	    strcat(data, ctime(&current_time));
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
