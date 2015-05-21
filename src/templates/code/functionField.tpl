<% define 'Field', :for => this do %>
	base_function(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		<% expand 'Params', :for => this %>
		aManager)<%idec%><%nonl%>
<% end %>

<% define 'Params', :for => this do %>
	params,
<% end %>