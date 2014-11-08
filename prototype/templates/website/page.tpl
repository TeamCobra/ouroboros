<% define 'Page', :for => Group do %>
	<html> <%iinc%>
	   <head> <%iinc%>
	      <title>Mongoose Server</title> <%idec%>
	   </head> <%idec%>
	
	<body> <%iinc%>
	   <h1><%= id %></h1>
	   
	   <% field.each do |field| %>
		   <label for="<%= field.id %>"><%= field.title.chardata[0].strip %></label>
		   <input type="text" id="<%= field.id %>" readonly><input type="text" id="<%= field.id %>_value">
		   <input type="button" value="Set" id="<%= field.id %>_button"><br>
	   <% end %> <%idec%>
	   	   
	</body>
	
	<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
	<script language="javascript" type="text/javascript"> <%iinc%>
	  $(function() { <%iinc%>
		$.ajax({ <%iinc%>
		  url: '/<%= id %>/get',
		  method: 'GET',
		  dataType: 'json',
		  success: function(json) { <%iinc%>
		  	<% field.each do |field| %>
		  		$('#<%= field.id %>').val(json.<%= field.id %>);
		  	<% end %>
		  } <%idec%>
		});
		
		<% field.each do |field| %>
			$("#<%= field.id %>_button").click(function(){ <%iinc%>
				$.ajax({ <%iinc%>
				  url: '/<%= id %>/<%= field.id %>/set',
				  method: 'POST',
				  data: { <%= field.id %>_value: $('#<%= field.id %>_value').val() },
				  dataType: 'json',
				  success: function(json) { <%iinc%>
				    $('#<%= field.id %>').val(json.<%= field.id %>);
				    $('#<%= field.id %>_value').val(""); <%idec%>
				  } <%idec%>
				}); <%idec%>
			}); 
		<% end %><%idec%> 
	  }); <%idec%>
	</script> <%idec%>
	</html>
<% end %>