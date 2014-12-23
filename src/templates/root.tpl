<% define 'Root' do %>
	<% file 'device_tree.cpp' do %>
		<% expand 'code/device_tree::Tree', :for => this %>
	<% end %>
<% end %>
