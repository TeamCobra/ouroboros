<% define 'Range', :for => this do %>
	<%
		if defined? this.min and not this.min.empty?
			min = this.min.chardata[0].strip
		else
			min = this.Min
		end
		if defined? this.max and not this.max.empty?
			max = this.max.chardata[0].strip
		else
			max = this.Max
		end
	%>
	std::pair<int,int>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>

<% define 'Field', :for => this do %>
	base_number<int, <%=this.Min%>, <%=this.Max%> >(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		<%= value.chardata[0].strip %>,
		<% expand 'Range', :for => this %>)<%idec%><%nonl%>
<% end %>
