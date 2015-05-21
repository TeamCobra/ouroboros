<% define 'Root' do %>
	<% file 'ouroboros/device_tree.cpp' do %>
		<% expand 'code/device_tree::Tree', :for => deviceConfig %>
	<% end %>
<% end %>
