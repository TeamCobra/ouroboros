<% define 'PrepareEnums', :for => this do %>
	std::map<std::string, int> <%= title.chardata[0].strip %>Map;
	<%
		$enumCounter = 0
		expand 'Enum', :for => value
	%>
<% end %>

<% define 'Enums', :for => this do %>
	std::map<std::string, int> <%= title.chardata[0].strip %>Map;
	<% expand 'Enum', :for => value %>
	std::pair<<%=this.Type%>,<%=this.Type%>>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>

<% define 'Enum', :for => this do %>
	std::map<std::string, int> <%= title.chardata[0].strip %>Map["<%= this.chardata[0].strip %>"] = <%= $enumCounter += 1 %>;
<% end %>

<% define 'Field', :for => this do %>
	base_enum(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		std::map<std::string, int> <%= title.chardata[0].strip %>Map)
<% end %>
