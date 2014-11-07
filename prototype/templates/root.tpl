<% define 'Root' do %>
	<% file 'server.c' do %>
		<% expand 'code/server::Server', :for => server %>
	<% end %>
	
	<% server.group.each do |group| %> 
		<% file group.id+'.html' do %>
			<% expand 'website/page::Page', :for => group %>
		<% end %>
	<% end %>
<% end %>
