<% define 'Tree', :for => this do %>
	#include <server/device_tree.tpp>
	#include <data/base.hpp>
	#include <data/base_string.h>
	#include <data/base_number.hpp>
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
	<%= parentGroupVar %><%= operator %><%nonl%><%nows%><%nows%><%nows%>
	<% if type === "intField" %>
		add(new <% expand 'signedIntField::Field', :for => this %>);
	<% elsif type === "stringField" %>
		add(new <% expand 'stringField::Field', :for => this %>);
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


