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
		<%= parentGroupVar %><%= operator %>add(new <% expand 'intField', :for => this %>);
	<% elsif type === "stringField" %>
		<%= parentGroupVar %><%= operator %>add(new <% expand 'stringField', :for => this %>);
	<% end %>
<% end %>

<% define 'intField', :for => this do %>
	base_integer(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		<%= value.chardata[0].strip %>,
		<% expand 'Range', :for => this %>)<%idec%><%nonl%>
<% end %>

<% define 'stringField', :for => this do %>
	base_string(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		"<%= value.chardata[0].strip %>",
		"",
		10,
		<% expand 'stringRange', :for => this %>)<%idec%><%nonl%>
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
	<% if not this.min.empty? %>
		<% min = this.min.chardata[0].strip %>
	<% else %>
		<% min = "std::numeric_limits<int>::min()" %>
	<% end %>
	<% if not this.max.empty? %>
		<% max = this.max.chardata[0].strip %>
	<% else %>
		<% max = "std::numeric_limits<int>::max()" %>
	<% end %>
	std::pair<int,int>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>

<% define 'stringRange', :for => this do %>
	<% if not this.minLength.empty? %>
		<% min = this.minLength.chardata[0].to_s.strip %>
	<% else %>
		<% min = "std::numeric_limits<int>::min()" %>
	<% end %>
	<% if not this.maxLength.empty? %>
		<% max = this.maxLength.chardata[0].to_s.strip %>
	<% else %>
		<% max = "std::numeric_limits<int>::max()" %>
	<% end %>
	std::pair<int,int>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>