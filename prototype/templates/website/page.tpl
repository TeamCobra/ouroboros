<% define 'Page', :for => Group do %>
	<html> <%iinc%>
	   <head> <%iinc%>
	      <title>Mongoose Server</title> <%idec%>
	   </head> 
	
	<body> <%iinc%>
	   <h1><%= id %></h1>
	   
	   <% field.each do |field| %>
		   <label for="<%= field.id %>"><%= field.title.chardata[0].strip %></label>
		   <input type="text" id="<%= field.id %>" readonly><input type="text" id="<%= field.id %>_value">
		   <input type="button" value="Set" id="<%= field.id %>_button"><br>
	   <% end %> <%idec%>
	   	   
	</body>
	
	<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
	<script src="<%= id %>.js"></script>
	
	</html>
<% end %>