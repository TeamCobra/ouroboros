<% define 'Field', :for => this do %>
	base_boolean(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		<%= !!value.chardata[0].strip %>)<%idec%><%nonl%>
<% end %>