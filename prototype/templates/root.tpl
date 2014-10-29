<% define 'Root' do %>
	<% file 'hello.c' do %>
		<% expand 'code/hello::Server', :for => server %>
	<% end %>
<% end %>
