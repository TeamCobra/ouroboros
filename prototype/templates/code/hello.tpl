<% define 'Server', :for => Server do %>
	#include <stdio.h>
	#include <string.h>
	#include "mongoose.h"
	
	<% expand 'Groups', :foreach => group %>
	
	static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
	  switch (ev) {
	    case MG_AUTH: return MG_TRUE;
	    case MG_REQUEST:
	      <% expand 'DisplayData', :foreach => group %>
	      return MG_TRUE;
	    default: return MG_FALSE;
	  }
	}
	
	int main(void) {
	  struct mg_server *server; <%nl%>
	  
	  <% expand 'InitializeStructs', :foreach => group %>
			
	  // Create and configure the server
	  server = mg_create_server(NULL, ev_handler);
	  mg_set_option(server, "listening_port", "<%= port %>");
	
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




<% define 'Groups', :for => this do %>
	<%nl%><% expand 'Fields', :foreach => field %><%nl%>
<% end %>

<% define 'Fields', :for => this do %>
	struct <%= id %>{
		char title[30];
		<% expand 'Type', :for => type[0] %>
	 };
	 struct <%= id %> <%= id %>;<%nl%>
<% end %>

<% define 'Type', :for => this do %>
	<% expand 'Integer', :for => integer[0] %>
<% end %>

<% define 'Integer', :for => this do %>
	int minInclusive;
	int value;
<% end %>




<% define 'InitializeStructs', :for => this do %>
	<%nl%><% expand 'InitializeFields', :foreach => field %><%nl%>
<% end %>

<% define 'InitializeFields', :for => this do %>
	strcpy(<%= id %>.title, "<%= title.chardata[0].strip %>");
	<% expand 'InitializeType', :for => type[0] %>
<% end %>

<% define 'InitializeType', :for => this do %>
	<% expand 'InitializeInteger', :for => integer[0] %>
<% end %>

<% define 'InitializeInteger', :for => this do %>
	<%= parent.parent.id %>.minInclusive = <%= minInclusive.chardata[0].strip %>;
	<%= parent.parent.id %>.value = <%= value.chardata[0].strip %>;
	<%nl%>
<% end %>




<% define 'DisplayData', :for => this do %>
	<%nl%><% expand 'DisplayField', :foreach => field %><%nl%>
<% end %>

<% define 'DisplayField', :for => this do %>
	<% expand 'DisplayType', :for => type[0] %>
<% end %>

<% define 'DisplayType', :for => this do %>
	<% expand 'DisplayInteger', :for => integer[0] %>
<% end %>

<% define 'DisplayInteger', :for => this do %>
	char buffer_<%= parent.parent.id %>[50];
	sprintf(buffer_<%= parent.parent.id %>, "%s %d\n", <%= parent.parent.id %>.title, <%= parent.parent.id %>.value);
	mg_printf_data(conn, buffer_<%= parent.parent.id %>, conn->uri);
<% end %>