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
				<% expand 'Field', :foreach => field %>
				<% expand 'Group', :foreach => group %>
				<% expand 'AddGroup', :foreach => group %>
				<%nl%>
				return result;
			<%idec%>}
		<%idec%>}
	<%idec%>}
<% end %>

<% define 'Field', :for => this do %>
	<% if parent.class.to_s === ServerModel::DeviceConfig.to_s %>
		<% parentGroupVar = 'result' %>
		<% operator = '.' %> 
	<% else %>
		<% parentGroupVar = parent.title.chardata[0].strip.downcase.delete(' ') %>
		<% operator = '->' %> 
	<% end %>
	<% if type === "intField" %>
		<%= parentGroupVar %><%= operator %>add(new base_integer("<%= title.chardata[0].strip %>", "<%= description.chardata[0].strip %>", <%= value.chardata[0].strip %>, <% expand 'Range', :for => this %>));
	<% elsif type === "stringField" %>
		<%= parentGroupVar %><%= operator %>add(new base_string("<%= title.chardata[0].strip %>", "<%= description.chardata[0].strip %>", "<%= value.chardata[0].strip %>", "", 10, {0, 10}));
	<% end %>
<% end %>

<% define 'Group', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	group<var_field> *<%= groupVar %> = new group<var_field>("<%= title.chardata[0].strip %>", "<%= description.chardata[0].strip %>");	
	<% expand 'Field', :foreach => field %>
	<% expand 'Group', :foreach => group %>
	<% expand 'AddGroup', :foreach => group %>
<% end %>

<% define 'AddGroup', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	<% if parent.class.to_s != ServerModel::DeviceConfig.to_s %>
		<%= parent.title.chardata[0].strip.downcase.delete(' ') %>->add(<%= groupVar %>);
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
