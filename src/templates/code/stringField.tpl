<% define 'Field', :for => this do %>
	base_string(<%iinc%>
		"<%= title.chardata[0].strip %>",
		"<%= description.chardata[0].strip %>",
		"<%= value.chardata[0].strip %>",
		<% expand 'Pattern', :for => this %>,
		<% expand 'Range', :for => this %>)<%idec%><%nonl%>
<% end %>


<% define 'Range', :for => this do %>
	<%
		if defined? this.minLength and not this.minLength.empty?
			min = this.minLength.chardata[0].to_s.strip
		else
			min = "std::numeric_limits<std::size_t>::min()"
		end
		if defined? this.maxLength and not this.maxLength.empty?
			max = this.maxLength.chardata[0].to_s.strip
		else
			max = "std::numeric_limits<std::size_t>::max()"
		end
	%>
	std::pair<std::size_t, std::size_t>(<%=min.to_s%>, <%=max.to_s%>)<%nonl%>
<% end %>

<% define 'Pattern', :for => this do %>
	<% 
		pattern = ""
		if defined? this.pattern and not this.pattern.empty?
			pattern = this.pattern.chardata[0].to_s.strip
		end
	%>
	"<%= pattern %>"<%nonl%>
<% end %>
