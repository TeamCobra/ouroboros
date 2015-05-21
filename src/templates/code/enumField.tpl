<% define 'PrepareEnums', :for => this do %>
	enumMap.clear();
	<%
		$enumCounter = 0
		expand 'Enum', :foreach => value
	%>
<% end %>

<% define 'Enum', :for => this do %>
	enumMap["<%= this.chardata[0].strip %>"] = <%= $enumCounter %>;
	<% $enumCounter += 1  %>
<% end %>

<% define 'Field', :for => this do %>
	base_enum(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		0,
		enumMap)<%idec%><%nonl%>
<% end %>
