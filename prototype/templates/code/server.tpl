<% define 'Server', :for => Server do %>
	#include <string.h>
	#include <time.h>
	#include "mongoose.h"
	#include <stdlib.h>
	
	<% expand 'Groups', :foreach => group %>
	
	<% group.each do |group| %>
		static int get_<%= group.id %>_page(struct mg_connection *conn) {
			mg_send_file(conn, "<%= group.id %>.html", NULL);
			return MG_MORE;
		}
		
		static void get_<%= group.id %>_values(struct mg_connection *conn){
			mg_printf_data(conn, "{ <% group.field.each_with_index do |field, i| %>\"<%= field.id %>\": %d<% if i != group.field.size - 1 %>, <% end %><% end %> }", <% group.field.each_with_index do |field, i| %><%= field.id %>.value<% if i != group.field.size - 1 %>, <% end %><% end %>);
		}
	<% end %>
	
	<%nl%>
	
	<% group.each do |group| %>
		<% group.field.each do |field| %>
			static void set_<%= field.id %>_value(struct mg_connection *conn){
				char value_str[100];
				mg_get_var(conn, "<%= field.id %>_value", value_str, sizeof(value_str));
				int value = atoi(value_str);
				<%= field.id %>.value = value;
				mg_printf_data(conn, "{ \"<%= field.id %>\": %d }", <%= field.id %>.value);
			}
		<% end %>
	<% end %>
	
	<%nl%>
	
	static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
	  switch (ev) {
	    case MG_AUTH: 
	    	return MG_TRUE;
	    case MG_REQUEST:
	    
	    	<% group.each do |group| %>
		    	if(!strcmp(conn->uri, "/<%= group.id %>")){
					return get_<%= group.id %>_page(conn);
				}
				if(!strcmp(conn->uri, "/<%= group.id %>/get")){
					get_<%= group.id %>_values(conn);
					return MG_TRUE;
				}
			<% end %>
			
			<% group.each do |group| %>
				<% group.field.each do |field| %>
					if(!strcmp(conn->uri, "/<%= group.id %>/<%= field.id %>/set")){
						set_<%= field.id %>_value(conn);
						return MG_TRUE;
					}
				<% end %>
			<% end %>
			
			return MG_FALSE;
	    default: return MG_FALSE;
	  }
	}
	
	<%nl%>
	
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
		<% expand 'Integer', :for => integer[0] %>
	 };
	 struct <%= id %> <%= id %>;<%nl%>
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
	<% expand 'InitializeInteger', :for => integer[0] %>
<% end %>

<% define 'InitializeInteger', :for => this do %>
	<%= parent.id %>.minInclusive = <%= minInclusive.chardata[0].strip %>;
	<%= parent.id %>.value = <%= value.chardata[0].strip %>;
	<%nl%>
<% end %>