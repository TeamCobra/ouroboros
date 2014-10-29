<% define 'Server', :for => Server do %>
	#include <stdio.h>
	#include <string.h>
	#include "mongoose.h"
	
	<%nl%><% expand 'Structs', :foreach => fields %><%nl%>
	
	static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
	  switch (ev) {
	    case MG_AUTH: return MG_TRUE;
	    case MG_REQUEST:
	      mg_printf_data(conn, "<% expand 'Response' %>", conn->uri);
	      return MG_TRUE;
	    default: return MG_FALSE;
	  }
	}
	
	int main(void) {
	  struct mg_server *server; <%nl%>
	  
	  <%nl%><% expand 'InitializeStructs', :foreach => fields %><%nl%>
	
	  // Create and configure the server
	  server = mg_create_server(NULL, ev_handler);
	  mg_set_option(server, "listening_port", "<% expand 'Port' %>");
	
	  // Serve request. Hit Ctrl-C to terminate the program
	  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
	  for (;;) {
	    mg_poll_server(server, 1000);
	  }
	
	  // Cleanup, and free server instance
	  mg_destroy_server(&server);
	
	  return 0;
	}
<% end %>

<% define 'Port', :for => Server do %>
	<%= port %><%nows%>
<% end %>

<% define 'Response', :for => Server do %>
	<%= response %><%nows%>
<% end %>

<% define 'Structs', :for => Field do %>
	typedef struct {
		char title[30];
		<%= type %> option;
	 } <%= structName %>; <%nl%>
<% end %>

<% define 'InitializeStructs', :for => Field do %>
	<%= structName %> <%= name %>;
	strcpy(<%= name %>.title, "<%= title %>");
	<%= name %>.option = 0;<%nl%>
<% end %>