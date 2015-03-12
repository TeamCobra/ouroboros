
<% nMax = -128 %>
<% nMin = 127 %>

<% define 'Range', :for => this do %>
	<% if defined? this.min and not this.min.empty? %>
		<% min = this.min.chardata[0].strip %>
	<% else %>
		<% min = nMin.to_s %>
	<% end %>
	<% if defined? this.max and not this.max.empty? %>
		<% max = this.max.chardata[0].strip %>
	<% else %>
		<% max = nMax.to_s %>
	<% end %>
	std::pair<int,int>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>

<% define 'Field', :for => this do %>
	base_number<int, <%=nMin%>, <%nMax%> >(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		<%= value.chardata[0].strip %>,
		<% expand 'Range', :for => this %>)<%idec%><%nonl%>
<% end %>
