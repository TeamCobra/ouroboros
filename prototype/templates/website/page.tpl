<% define 'Page', :for => Group do %>
	<html>
	   <head>
	      <title>Mongoose Server</title>
	   </head>
	
	<body>
	   <h1><%= id %></h1>
	   
	   <% field.each do |field| %>
		   <label for="<%= field.id %>"><%= field.title.chardata[0].strip %></label>
		   <input type="text" id="<%= field.id %>" readonly><input type="text" id="<%= field.id %>_value"><input type="button" value="Set" id="<%= field.id %>_button"><br>
	   <% end %>
	   	   
	</body>
	
	<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
	<script language="javascript" type="text/javascript">
	  $(function() {
		$.ajax({
		  url: '/<%= id %>/get',
		  method: 'GET',
		  dataType: 'json',
		  success: function(json) {
		  	<% field.each do |field| %>
		  		$('#<%= field.id %>').val(json.<%= field.id %>);
		  	<% end %>
		  }
		});
		
		<% field.each do |field| %>
			$("#<%= field.id %>_button").click(function(){
				$.ajax({
				  url: '/<%= id %>/<%= field.id %>/set',
				  method: 'POST',
				  data: { <%= field.id %>_value: $('#<%= field.id %>_value').val() },
				  dataType: 'json',
				  success: function(json) {
				    $('#<%= field.id %>').val(json.<%= field.id %>);
				    $('#<%= field.id %>_value').val("");
				  }
				});
			});
		<% end %> 
	  });
	</script>
	</html>
<% end %>