<% define 'Root' do %>
	<% file 'device_tree.cpp' do %>
		<% expand 'code/device_tree::Tree', :for => deviceConfig %>
	<% end %>
<% end %>
