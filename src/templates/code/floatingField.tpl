<% define 'Range', :for => this do %>
	<%
		if this.min.size > 0
			min = this.min.chardata[0].strip
		else
			min = this.Min
		end
		if this.max.size > 0
			max = this.max.chardata[0].strip
		else
			max = this.Max
		end
	%>
	std::pair<<%=this.Type%>,<%=this.Type%>>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>

<% define 'Field', :for => this do %>
	base_floating<<%= this.Type %>>(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		<%= value.chardata[0].strip %>,
		<% expand 'Range', :for => this %>)<%idec%><%nonl%>
<% end %>
