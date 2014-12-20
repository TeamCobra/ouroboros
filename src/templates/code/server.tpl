<% define 'Server', :for => DeviceConfig do %>
	#include <string.h>
	#include <time.h>
	#include "mongoose.h"
	#include <stdlib.h>
	
	<% expand 'Groups', :foreach => group %> 
	
	static int get_config(struct mg_connection *conn) { <%iinc%>
			mg_send_file(conn, "config.json", NULL);
			return MG_MORE; <%idec%>
		}
	<% group.each do |group| %>
		static int get_<%= group.id %>_page(struct mg_connection *conn) { <%iinc%>
			mg_send_file(conn, "<%= group.id %>.html", NULL);
			return MG_MORE; <%idec%>
		}

		static int get_<%= group.id %>_js(struct mg_connection *conn) { <%iinc%>
			mg_send_file(conn, "<%= group.id %>.js", NULL);
			return MG_MORE; <%idec%>
		}
		
		static void get_<%= group.id %>_values(struct mg_connection *conn){ <%iinc%>
			mg_printf_data(conn, "{ <% group.field.each_with_index do |field, i| %>\"<%= field.id %>\": %d<% if i != group.field.size - 1 %>, <% end %><% end %> }", <% group.field.each_with_index do |field, i| %><%= field.id %>.value<% if i != group.field.size - 1 %>, <% end %><% end %>); <%idec%>
		}
	<% end %>
	
	<%nl%>
	
	<% group.each do |group| %>
		<% group.field.each do |field| %>
			static void set_<%= field.id %>_value(struct mg_connection *conn){ <%iinc%>
				char value_str[100];
				mg_get_var(conn, "<%= field.id %>_value", value_str, sizeof(value_str));
				int value = atoi(value_str);
				<%= field.id %>.value = value;
				mg_printf_data(conn, "{ \"<%= field.id %>\": %d }", <%= field.id %>.value); <%idec%>
			}
		<% end %>
	<% end %>
	
	<%nl%>
	
	static int ev_handler(struct mg_connection *conn, enum mg_event ev) { <%iinc%>
	  switch (ev) { <%iinc%>
	    case MG_AUTH: <%iinc%>
	    	return MG_TRUE; <%idec%>
	    case MG_REQUEST: <%iinc%>
	    	if(!strcmp(conn->uri, "/config.json")){ <%iinc%>
            return get_config(conn); 
         }
	    	<% group.each do |group| %>
	    	if(!strcmp(conn->uri, "/<%= group.id %>.js")){ <%iinc%>
					return get_<%= group.id %>_js(conn); <%idec%>
				}
		    if(!strcmp(conn->uri, "/<%= group.id %>")){ <%iinc%>
					return get_<%= group.id %>_page(conn); <%idec%>
				}
				if(!strcmp(conn->uri, "/<%= group.id %>/get")){ <%iinc%>
					get_<%= group.id %>_values(conn);
					return MG_TRUE; <%idec%>
				}
			<% end %>
			
			<% group.each do |group| %>
				<% group.field.each do |field| %>
					if(!strcmp(conn->uri, "/<%= group.id %>/<%= field.id %>/set")){ <%iinc%>
						set_<%= field.id %>_value(conn);
						return MG_TRUE; <%idec%>
					}
				<% end %>
			<% end %>
			
			return MG_FALSE;
	    default: return MG_FALSE; <%idec%><%idec%>
	  } <%idec%>
	}<%idec%>
	
	<%nl%>
	
	int main(void) { <%iinc%>
	  struct mg_server *server; <%nl%>
	  
	  <% expand 'InitializeStructs', :foreach => group %>
			
	  // Create and configure the server
	  server = mg_create_server(NULL, ev_handler);
	  mg_set_option(server, "listening_port", "<%= port %>");
	
	  // Serve request. Hit Ctrl-C to terminate the program
	  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
	  for (;;) { <%iinc%>
	    mg_poll_server(server, 1000); <%idec%>
	  }
	
	  // Cleanup, and free server instance
	  mg_destroy_server(&server);
	
	  return 0; <%idec%>
	}
<% end %>




<% define 'Groups', :for => this do %>
	<%nl%><% expand 'Fields', :foreach => field %><%nl%>
<% end %>

<% define 'Fields', :for => this do %>
	struct <%= id %>{ <%iinc%>
		char title[30];
		<% expand 'Integer', :for => integer[0] %> <%idec%>
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
