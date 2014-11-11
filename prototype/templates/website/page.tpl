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
		  	<% end %> <%idec%>
		  } <%idec%>
		});
		
			var updateValue = function(event) {<%iinc%>
				event.preventDefault();

				var targetId = event.target.id.replace("_button","");
				var url = '/lights/' + targetId + '/set';

				// we need to make a request data object so we can add the dynamically
				// created keys to send or it doesnt work
				var requestData = {};
				var value = targetId + '_value';
				var fieldValue = $('#' + targetId + '_value').val();
				requestData[value] = fieldValue;
				
				$.ajax({ <%iinc%>
				  url: url,
				  method: 'POST',
				  data: requestData,
				  dataType: 'json',
				  success: function(json) { <%iinc%>
				    $('#' + targetId).val(json[targetId]);
				    $('#' + targetId + '_value').val(""); <%idec%>
				  } <%idec%>
				}); <%idec%>
			}; 

		<% field.each do |field| %>
			$("#<%= field.id %>_button").click(updateValue);
		<% end %><%idec%>

	  }); <%idec%>
	</script> <%idec%>
	</html>
<% end %>