<% define 'Tree', :for => this do %>
	
	#include <server/device_tree.tpp>
	#include <data/base.hpp>
	#include <data/base_string.h>
	#include <data/base_integer.h>
	#include <string>
	#include <limits>
	<%nl%>
	namespace ouroboros
	{<%iinc%>
		namespace detail
		{<%iinc%>
			template<>
			group<var_field> build_tree()
			{<%iinc%>
			
				group<var_field> result("server", "Root node.");
				
				<% if defined? this.field %>
					<% field.each do |field| %>
						<% if field.type === "intField" %>
							result.add(new base_integer("<%= field.title.chardata[0].strip %>", "<%= field.description.chardata[0].strip %>", <%= field.value.chardata[0].strip %>, <% expand 'Range', :for => field %>));
						<% elsif field.type === "stringField" %>
							result.add(new base_string("<%= field.title.chardata[0].strip %>", "", "", "", 10, {0, 10}));
						<% end %>
					<% end %>
				<% end %>
				<%nl%>
				<% if defined? this.group %>		
					<% expand 'Group', :foreach => group %>
					<% expand 'AddGroup', :foreach => group %>
				<% end %>
				<%nl%>
				return result;
			<%idec%>}
		<%idec%>}
	<%idec%>}
<% end %>

<% define 'Group', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	group<var_field> *<%= groupVar %> = new group<var_field>("<%= title.chardata[0] %>", "<%= description.chardata[0].strip %>");	
	<% field.each do |field| %>
		<%= groupVar %>->add(new base_string("<%= field.title.chardata[0].strip %>", "", "", "", 10, {0, 10}));
	<% end %>
	<%nl%>
	<% if defined? this.group %>		
		<% expand 'Group', :foreach => group %>
		<% expand 'AddGroup', :foreach => group %>
	<% end %>
<% end %>

<% define 'AddGroup', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	<% if defined? this.parent.title %>
		<%= parent.title.chardata[0].strip.downcase.delete(' ') %>->add(<%= groupVar%>);
	<% else %>
		result.add(<%= groupVar %>);
	<% end %>
<% end %>

<% define 'Range', :for => this do %>
	<% if defined? this.minInclusive %>
		<% min = this.minInclusive %>;
	<% else %>
		<% min = "std::numeric_limits<int>::min()" %>
	<% end %>
	<% if defined? this.maxInclusive %>
		<% max = this.maxInclusive %>;
	<% else %>
		<% max = "std::numeric_limits<int>::max()" %>
	<% end %>
	{<%=min.to_s%>, <%=max.to_s%>}<%nonl%>
<% end %>
