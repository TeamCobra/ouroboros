<% define 'Index', :for => Group do %>
$(function() { <%iinc%>
  loadJSON();
  loadGroups();
  <% field.each do |field| %>
  $("#<%= field.id %>_button").click(updateValue);
  <% end %><%idec%>
}); <%idec%>

var groups;

var loadJSON = function() {
  $.getJSON( "config.json", function( data ) {
    groups = data.groups;
    loadNavigation();
  });
}

var loadGroups = function() {
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
}

var loadNavigation = function() {
  for (i in groups) {
    $link = $("<a href='/" + groups[i] + "'>" + groups[i] + "</a>")
    $('nav').append($link)
  }
}

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
<% end %>