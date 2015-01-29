<% define 'Config', for: DeviceConfig do %>

{
  <%# we need to use '+' for concatenation because using the normal %>
  <%# string injection that ruby uses wont work for single quotes, and %>
  <%# we have need double quotes for valid JSON %>
  "groups": [ <%= group.map {|g| '"' + g.id + '"' }.join(',') %> ]
}

<% end %>


